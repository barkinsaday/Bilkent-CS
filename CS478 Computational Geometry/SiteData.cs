using System.Collections.Generic;
using UnityEngine;

public class SiteData : MonoBehaviour {
    public List<Vector2> cellVertices = new List<Vector2>();
    public Color siteColor;

    private void Awake() {
        siteColor = Random.ColorHSV(0f, 1f, 0.5f, 1f, 0.8f, 1f); // Random bright color
    }
}
