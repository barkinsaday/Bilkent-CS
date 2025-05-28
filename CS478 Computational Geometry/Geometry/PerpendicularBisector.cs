using UnityEngine;

public class PerpendicularBisector {
    public Vector2 point;       // Midpoint
    public Vector2 direction;   // Normalized perpendicular direction

    public PerpendicularBisector(Vector2 siteA, Vector2 siteB) {
        point = (siteA + siteB) / 2f;
        Vector2 delta = siteB - siteA;
        direction = new Vector2(-delta.y, delta.x).normalized;
    }

    // For drawing, this returns a point along the bisector
    public Vector2 GetPoint(float t) {
        return point + direction * t;
    }
}
