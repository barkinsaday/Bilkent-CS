using System.Collections.Generic;
using UnityEngine;
using MIConvexHull;

public static class VoronoiGenerator
{
    public static List<VoronoiRegion> ComputeVoronoi(List<Vertex2> sites, Rect boundingArea, Dictionary<Vector2, Color> previousColors)
    {
        var regions = new List<VoronoiRegion>();

        // Step 1: Add bounding triangle vertices
        float padding = Mathf.Max(boundingArea.width, boundingArea.height) * 5f;

        Vector2 center = boundingArea.center;
        Vector2 p1 = center + new Vector2(-2 * padding, -padding);
        Vector2 p2 = center + new Vector2(2 * padding, -padding);
        Vector2 p3 = center + new Vector2(0, 2 * padding);

        var extendedSites = new List<Vertex2>(sites)
        {
            new Vertex2(p1),
            new Vertex2(p2),
            new Vertex2(p3)
        };

        // Step 2: Delaunay triangulation
        var delaunay = DelaunayTriangulation<Vertex2, DefaultTriangulationCell<Vertex2>>.Create(extendedSites, 1e-10);

        // Step 3: Map from each site to its Voronoi region (as list of circumcenters)
        Dictionary<Vertex2, List<Vector2>> siteToRegion = new Dictionary<Vertex2, List<Vector2>>();

        foreach (var cell in delaunay.Cells)
        {
            Vector2 a = cell.Vertices[0].ToVector2();
            Vector2 b = cell.Vertices[1].ToVector2();
            Vector2 c = cell.Vertices[2].ToVector2();

            Vector2 circumcenter = ComputeCircumcenter(a, b, c);

            foreach (var site in cell.Vertices)
            {
                if (!siteToRegion.ContainsKey(site))
                    siteToRegion[site] = new List<Vector2>();

                siteToRegion[site].Add(circumcenter);
            }
        }

        // Step 4: Finalize Voronoi cells (exclude artificial triangle sites)
        foreach (var kvp in siteToRegion)
        {
            if (!sites.Contains(kvp.Key))
                continue; // skip artificial points

            var sorted = SortPolygonVertices(kvp.Value);
            Color reuseColor = Color.white;
            Vector2 pos = kvp.Key.ToVector2();

            if (previousColors.TryGetValue(pos, out Color existingColor))
                reuseColor = existingColor;

            var region = new VoronoiRegion
            {
                site = kvp.Key,
                vertices = sorted,
                color = reuseColor
            };

            regions.Add(region);
        }

        // Step 5: Build adjacency map
        Dictionary<VoronoiRegion, HashSet<VoronoiRegion>> adjacencyMap = new Dictionary<VoronoiRegion, HashSet<VoronoiRegion>>();

        for (int i = 0; i < regions.Count; i++)
        {
            for (int j = i + 1; j < regions.Count; j++)
            {
                var a = regions[i];
                var b = regions[j];

                if (AreRegionsNeighbors(a.vertices, b.vertices))
                {
                    if (!adjacencyMap.ContainsKey(a))
                        adjacencyMap[a] = new HashSet<VoronoiRegion>();
                    if (!adjacencyMap.ContainsKey(b))
                        adjacencyMap[b] = new HashSet<VoronoiRegion>();

                    adjacencyMap[a].Add(b);
                    adjacencyMap[b].Add(a);
                }
            }
        }

        // Step 6: Apply greedy coloring
        List<Color> colorPalette = GenerateColorPalette(100);
        Dictionary<VoronoiRegion, Color> regionColors = new Dictionary<VoronoiRegion, Color>();

        foreach (var region in regions)
        {
            HashSet<Color> usedColors = new HashSet<Color>();
            if (adjacencyMap.TryGetValue(region, out var neighbors))
            {
                foreach (var neighbor in neighbors)
                {
                    if (regionColors.TryGetValue(neighbor, out var usedColor))
                        usedColors.Add(usedColor);
                }
            }

            if (region.color == Color.white)
            {
                foreach (var color in colorPalette)
                {
                    if (!usedColors.Contains(color))
                    {
                        regionColors[region] = color;
                        break;
                    }
                }

                if (!regionColors.ContainsKey(region))
                    regionColors[region] = Random.ColorHSV(); // fallback
            }
            else
            {
                regionColors[region] = region.color; // reuse
            }

            region.color = regionColors[region];
        }



        // Step 7: Assign final colors
        foreach (var region in regions)
        {
            region.color = regionColors[region];
        }


        return regions;
    }

    private static Vector2 ComputeCircumcenter(Vector2 a, Vector2 b, Vector2 c)
    {
        float d = 2 * (a.x * (b.y - c.y) +
                       b.x * (c.y - a.y) +
                       c.x * (a.y - b.y));

        float ux = ((a.sqrMagnitude) * (b.y - c.y) +
                    (b.sqrMagnitude) * (c.y - a.y) +
                    (c.sqrMagnitude) * (a.y - b.y)) / d;

        float uy = ((a.sqrMagnitude) * (c.x - b.x) +
                    (b.sqrMagnitude) * (a.x - c.x) +
                    (c.sqrMagnitude) * (b.x - a.x)) / d;

        return new Vector2(ux, uy);
    }

    private static List<Vector2> SortPolygonVertices(List<Vector2> points)
    {
        Vector2 center = Vector2.zero;
        foreach (var pt in points)
            center += pt;
        center /= points.Count;

        points.Sort((a, b) =>
        {
            float angleA = Mathf.Atan2(a.y - center.y, a.x - center.x);
            float angleB = Mathf.Atan2(b.y - center.y, b.x - center.x);
            return angleA.CompareTo(angleB);
        });

        return points;
    }

    private static bool AreRegionsNeighbors(List<Vector2> a, List<Vector2> b)
    {
        int shared = 0;
        foreach (var pa in a)
        {
            foreach (var pb in b)
            {
                if (Vector2.Distance(pa, pb) < 0.01f)
                {
                    shared++;
                    if (shared >= 2) return true; // regions share an edge
                }
            }
        }
        return false;
    }

    private static List<Color> GenerateColorPalette(int count)
    {
        List<Color> palette = new List<Color>();
        float goldenRatioConjugate = 0.61803398875f;
        float hue = Random.value;

        for (int i = 0; i < count; i++)
        {
            hue += goldenRatioConjugate;
            hue %= 1f;

            float saturation = Random.Range(0.5f, 1f); // wider sat range
            float value = Random.Range(0.8f, 1f);      // brighter but varied

            palette.Add(Color.HSVToRGB(hue, saturation, value));
        }

        return palette;
    }




}

