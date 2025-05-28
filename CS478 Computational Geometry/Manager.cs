using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;

public enum VoronoiAlgorithm
{
    RIC,
    Fortune
}


public class Manager : MonoBehaviour
{
    [Header("UI References")]
    public TMP_InputField pointCountInput;
    public TMP_Dropdown distributionDropdown;
    public TMP_Dropdown algorithmDropdown; // Add this line



    [Header("Prefabs and References")]
    public GameObject sitePointPrefab;
    public VoronoiRenderer voronoiRenderer;

    [Header("Site Bounds")]
    public Vector2 minBounds;
    public Vector2 maxBounds;

    [Header("Simulation Settings")]
    public float totalSimulationTime; // total time for entire animation


    //Privates
    private List<GameObject> siteObjects = new List<GameObject>();
    private List<Vertex2> siteVertices = new List<Vertex2>();
    private Dictionary<Vector2, Color> persistentColors = new Dictionary<Vector2, Color>();


    void Update()
    {
        if (Input.GetMouseButtonDown(0) && !EventSystem.current.IsPointerOverGameObject())
        {
            InsertSiteAtMousePosition();
        }
    }

    private void InsertSiteAtMousePosition()
    {
        Vector3 worldPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        Vector2 sitePos = new Vector2(worldPos.x, worldPos.y);

        GameObject site = Instantiate(sitePointPrefab, sitePos, Quaternion.identity);
        siteObjects.Add(site);
        siteVertices.Add(new Vertex2(sitePos));

        //persistentColors[sitePos] = FixedColorPalette.GetNextColor();

        RebuildVoronoi();
    }

    public void OnGenerateButtonClicked()
    {
        ClearSites();

        int count = ParseInputPointCount();
        if (count <= 0)
        {
            Debug.LogWarning("Invalid input.");
            return;
        }

        int selected = distributionDropdown.value;

        if (selected == 0) // Uniform
            GenerateUniformSites(count);
        else if (selected == 1) // Gaussian
            GenerateGaussianSites(count);
        else{
            Debug.LogWarning("Unknown distribution selected.");GenerateUniformSites(count);
        }
            

        RebuildVoronoi();
    }

    public void OnClearButtonClicked()
    {
        foreach (var obj in siteObjects)
            Destroy(obj);

        siteObjects.Clear();
        siteVertices.Clear();
        voronoiRenderer.Clear();
    }

    private void RebuildVoronoi()
    {
        var stopwatch = System.Diagnostics.Stopwatch.StartNew();

        voronoiRenderer.Clear();

        Rect bounds = new Rect(minBounds, maxBounds - minBounds);
        VoronoiAlgorithm selectedAlgorithm = (VoronoiAlgorithm)algorithmDropdown.value;

        if (selectedAlgorithm == VoronoiAlgorithm.RIC)
        {
            var regions = VoronoiGenerator.ComputeVoronoi(siteVertices, bounds, persistentColors);
            voronoiRenderer.DrawRegions(regions);

            persistentColors.Clear();
            foreach (var region in regions)
                persistentColors[region.site.ToVector2()] = region.color;
        }
        else if (selectedAlgorithm == VoronoiAlgorithm.Fortune)
        {
            var fortuneResult = FortuneVoronoiGenerator.ComputeVoronoi(siteVertices.ConvertAll(v => v.ToVector2()), bounds);
            foreach (var edge in fortuneResult.edges)
            {
                Debug.LogError($"Edge from {edge.start} to {(edge.end.HasValue ? edge.end.Value.ToString() : "null")}");
            }

            voronoiRenderer.DrawEdges(fortuneResult.edges);
        }
        stopwatch.Stop();
        Debug.LogError($"RebuildVoronoi() took {stopwatch.ElapsedMilliseconds} ms");
    }

    private int ParseInputPointCount()
    {
        if (int.TryParse(pointCountInput.text.Trim(), out int result))
            return result;

        return -1;
    }

    public void ClearSites()
    {
        Debug.Log("CLEAR Button Clicked:");

        foreach (var site in siteObjects)
        {
            if (site != null)
                Destroy(site);
        }

        siteObjects.Clear();
        siteVertices.Clear();
        voronoiRenderer.Clear();
    }

    //Simulate (Animate)
    public void OnSimulateButtonClicked()
    {
        OnClearButtonClicked(); // reset

        int count = ParseInputPointCount();
        if (count <= 0)
        {
            Debug.LogWarning("Invalid input.");
            return;
        }

        List<Vector2> generatedSites = new List<Vector2>();

        int selected = distributionDropdown.value;
        if (selected == 0) // Uniform
        {
            for (int i = 0; i < count; i++)
            {
                Vector2 pos = new Vector2(
                    Random.Range(minBounds.x, maxBounds.x),
                    Random.Range(minBounds.y, maxBounds.y)
                );
                generatedSites.Add(pos);
            }
        }
        else if (selected == 1) // Gaussian
        {
            float meanX = (minBounds.x + maxBounds.x) / 2f;
            float meanY = (minBounds.y + maxBounds.y) / 2f;
            float stdDevX = (maxBounds.x - minBounds.x) / 6f;
            float stdDevY = (maxBounds.y - minBounds.y) / 6f;

            for (int i = 0; i < count; i++)
            {
                float x = NextGaussian(meanX, stdDevX);
                float y = NextGaussian(meanY, stdDevY);
                x = Mathf.Clamp(x, minBounds.x, maxBounds.x);
                y = Mathf.Clamp(y, minBounds.y, maxBounds.y);

                generatedSites.Add(new Vector2(x, y));
            }
        }
        else
        {
            Debug.LogWarning("Unknown distribution selected.");
            return;
        }

        Shuffle(generatedSites);
        StartCoroutine(SimulateSiteInsertions(generatedSites));
    }


    private System.Collections.IEnumerator SimulateSiteInsertions(List<Vector2> siteSequence)
    {
        int count = siteSequence.Count;
        float delay = (count > 0) ? totalSimulationTime / count : 0.1f;

        foreach (var pos in siteSequence)
        {
            GameObject site = Instantiate(sitePointPrefab, pos, Quaternion.identity);
            siteObjects.Add(site);
            siteVertices.Add(new Vertex2(pos));

            RebuildVoronoi();
            yield return new WaitForSeconds(delay);
        }
    }


    private void Shuffle<T>(List<T> list)
    {
        for (int i = list.Count - 1; i > 0; i--)
        {
            int j = Random.Range(0, i + 1);
            (list[i], list[j]) = (list[j], list[i]);
        }
    }

    public List<GameObject> GetSiteObjects(){return siteObjects;}


    //Disributions
    private void GenerateUniformSites(int count)
    {
        for (int i = 0; i < count; i++)
        {
            Vector2 pos = new Vector2(
                Random.Range(minBounds.x, maxBounds.x),
                Random.Range(minBounds.y, maxBounds.y)
            );

            GameObject site = Instantiate(sitePointPrefab, pos, Quaternion.identity);
            siteObjects.Add(site);
            siteVertices.Add(new Vertex2(pos));
        }
    }

    private void GenerateGaussianSites(int count)
    {
        float meanX = (minBounds.x + maxBounds.x) / 2f;
        float meanY = (minBounds.y + maxBounds.y) / 2f;
        float stdDevX = (maxBounds.x - minBounds.x) / 6f;
        float stdDevY = (maxBounds.y - minBounds.y) / 6f;

        for (int i = 0; i < count; i++)
        {
            float x = NextGaussian(meanX, stdDevX);
            float y = NextGaussian(meanY, stdDevY);

            // Optional clamp to bounds
            x = Mathf.Clamp(x, minBounds.x, maxBounds.x);
            y = Mathf.Clamp(y, minBounds.y, maxBounds.y);

            Vector2 pos = new Vector2(x, y);
            GameObject site = Instantiate(sitePointPrefab, pos, Quaternion.identity);
            siteObjects.Add(site);
            siteVertices.Add(new Vertex2(pos));
        }
    }

    private float NextGaussian(float mean, float stdDev)
    {
        float u1 = 1f - Random.value;
        float u2 = 1f - Random.value;
        float randStdNormal = Mathf.Sqrt(-2f * Mathf.Log(u1)) * Mathf.Sin(2f * Mathf.PI * u2);
        return mean + stdDev * randStdNormal;
    }



}

/*
    Scale "site objects" based on zoom
    try to fix the same coloring for adjacent regions when dyanmically inserting
    if the above statemtnt is fixed, we can simulate animation by "click" inserting the sites on pre-computed batch input


*/
