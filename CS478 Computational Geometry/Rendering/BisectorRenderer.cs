using System.Collections.Generic;
using UnityEngine;

public class BisectorRenderer : MonoBehaviour {
    private List<LineRenderer> bisectorLines = new List<LineRenderer>();

    public void DrawBisector(Vector2 start, Vector2 end, Color? color = null) {
        GameObject go = new GameObject("BisectorLine");
        var lr = go.AddComponent<LineRenderer>();
        lr.positionCount = 2;
        lr.SetPosition(0, start);
        lr.SetPosition(1, end);
        lr.widthMultiplier = 0.05f;
        lr.loop = false;
        lr.useWorldSpace = true;

        lr.material = new Material(Shader.Find("Sprites/Default"));
        lr.startColor = lr.endColor = color ?? Color.green;

        bisectorLines.Add(lr);
    }

    public void ClearBisectors() {
        foreach (var lr in bisectorLines) {
            if (lr != null) Destroy(lr.gameObject);
        }
        bisectorLines.Clear();
    }
}
