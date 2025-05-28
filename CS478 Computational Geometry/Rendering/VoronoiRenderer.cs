using System.Collections.Generic;
using UnityEngine;

public class VoronoiRenderer : MonoBehaviour
{
    private List<GameObject> renderObjects = new List<GameObject>();

    public void Clear()
    {
        foreach (var obj in renderObjects)
        {
            if (obj != null)
                Destroy(obj);
        }
        renderObjects.Clear();
    }

    public void DrawRegions(List<VoronoiRegion> regions)
    {
        for (int i = 0; i < regions.Count; i++)
        {
            var region = regions[i];
            if (region.vertices.Count < 3) continue;

            // Create filled polygon
            GameObject fillObj = new GameObject("RegionFill");
            var mf = fillObj.AddComponent<MeshFilter>();
            var mr = fillObj.AddComponent<MeshRenderer>();
            mr.material = new Material(Shader.Find("Sprites/Default"));
            mr.material.color = region.color;

            mf.mesh = CreatePolygonMesh(region.vertices);

            // Set layer to be behind sites
            fillObj.transform.position = new Vector3(0, 0, 1f); // positive z pushes it behind

            renderObjects.Add(fillObj);

            // Create black outline
            GameObject lineObj = new GameObject("RegionOutline");
            var lr = lineObj.AddComponent<LineRenderer>();
            lr.positionCount = region.vertices.Count + 1;
            lr.loop = true;
            lr.widthMultiplier = 0.15f;
            lr.useWorldSpace = true;
            lr.material = new Material(Shader.Find("Sprites/Default"));
            lr.startColor = lr.endColor = Color.black;

            for (int j = 0; j < region.vertices.Count; j++)
                lr.SetPosition(j, region.vertices[j]);
            lr.SetPosition(region.vertices.Count, region.vertices[0]);

            renderObjects.Add(lineObj);
        }
    }

    private Mesh CreatePolygonMesh(List<Vector2> vertices)
    {
        Mesh mesh = new Mesh();
        Vector3[] verts3D = new Vector3[vertices.Count];
        for (int i = 0; i < vertices.Count; i++)
            verts3D[i] = vertices[i];

        Triangulator triangulator = new Triangulator(vertices.ToArray());
        int[] indices = triangulator.Triangulate();

        mesh.vertices = verts3D;
        mesh.triangles = indices;
        mesh.RecalculateNormals();
        mesh.RecalculateBounds();
        return mesh;
    }

    public void DrawEdges(List<FortuneVoronoiGenerator.VoronoiEdge> edges)
    {
        Clear();
        foreach (var edge in edges)
        {
            if (edge.end.HasValue)
            {
                GameObject lineObj = new GameObject("VoronoiEdge");
                var lr = lineObj.AddComponent<LineRenderer>();
                lr.positionCount = 2;
                lr.SetPosition(0, edge.start);
                lr.SetPosition(1, edge.end.Value);
                lr.widthMultiplier = 0.1f;
                lr.material = new Material(Shader.Find("Sprites/Default"));
                lr.startColor = lr.endColor = Color.black;
                renderObjects.Add(lineObj);
            }
        }
    }

}


