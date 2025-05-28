using UnityEngine;

public class CameraController : MonoBehaviour {
    [SerializeField] private float baseScreenSize = 20f;  // desired screen size in pixels
    [SerializeField] private float minScale = 0.1f;
    [SerializeField] private float maxScale = 0.5f;

    public float zoomSpeed;
    public float moveSpeed;
    private Camera cam;
    private Manager manager;


    void Start() {
        cam = Camera.main;
        manager = FindObjectOfType<Manager>();
    }

    void Update() {
        // Zoom
        float scroll = Input.GetAxis("Mouse ScrollWheel");
        cam.orthographicSize -= scroll * zoomSpeed;
        cam.orthographicSize = Mathf.Clamp(cam.orthographicSize, 2f, 100f);

        // Pan
        if(Input.GetMouseButton(2)) { // Middle mouse drag
            float x = -Input.GetAxis("Mouse X") * moveSpeed;
            float y = -Input.GetAxis("Mouse Y") * moveSpeed;
            cam.transform.Translate(new Vector3(x, y, 0));
        }

        UpdateSiteScales();
    }

    

    private void UpdateSiteScales()
    {
        if (manager == null) return;

        Camera cam = Camera.main;

        // Convert 1 world unit to screen space to determine zoom level effect
        Vector3 worldPoint = cam.transform.position;
        Vector3 screenPoint1 = cam.WorldToScreenPoint(worldPoint);
        Vector3 screenPoint2 = cam.WorldToScreenPoint(worldPoint + Vector3.right); // 1 world unit to the right

        float pixelsPerUnit = Mathf.Abs(screenPoint2.x - screenPoint1.x);

        // Compute the scale that makes the site appear as baseScreenSize pixels
        float scaleFactor = baseScreenSize / pixelsPerUnit;

        // Clamp the scale to avoid too small or too big dots
        scaleFactor = Mathf.Clamp(scaleFactor, minScale, maxScale);

        foreach (var site in manager.GetSiteObjects())
        {
            if (site != null)
                site.transform.localScale = Vector3.one * scaleFactor;
        }
    }


}
