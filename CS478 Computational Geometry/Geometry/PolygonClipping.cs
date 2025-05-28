using System.Collections.Generic;
using UnityEngine;

public static class PolygonClipping
{
    // Clips a convex polygon against a half-plane defined by linePoint and lineDir
    public static List<Vector2> ClipPolygon(List<Vector2> polygon, Vector2 linePoint, Vector2 lineDir)
    {
        List<Vector2> newPolygon = new List<Vector2>();
        int count = polygon.Count;

        for (int i = 0; i < count; i++)
        {
            Vector2 current = polygon[i];
            Vector2 next = polygon[(i + 1) % count];

            bool currentInside = IsOnPositiveSide(current, linePoint, lineDir);
            bool nextInside = IsOnPositiveSide(next, linePoint, lineDir);

            if (currentInside && nextInside)
            {
                newPolygon.Add(next);
            }
            else if (currentInside && !nextInside)
            {
                Vector2 intersection = LineIntersection(current, next, linePoint, lineDir);
                newPolygon.Add(intersection);
            }
            else if (!currentInside && nextInside)
            {
                Vector2 intersection = LineIntersection(current, next, linePoint, lineDir);
                newPolygon.Add(intersection);
                newPolygon.Add(next);
            }
            // else: both outside → discard edge
        }

        return newPolygon;
    }

    // Checks if a point is on the positive side of the line (using cross product)
    public static bool IsOnPositiveSide(Vector2 point, Vector2 linePoint, Vector2 lineDir)
    {
        Vector2 toPoint = point - linePoint;
        float cross = lineDir.x * toPoint.y - lineDir.y * toPoint.x;
        return cross > 0f;
    }

    // Finds intersection between a segment and an infinite line
    public static Vector2 LineIntersection(Vector2 segA, Vector2 segB, Vector2 linePoint, Vector2 lineDir)
    {
        Vector2 segDir = segB - segA;
        Vector2 diff = segA - linePoint;
        float cross = segDir.x * lineDir.y - segDir.y * lineDir.x;

        if (Mathf.Abs(cross) < 1e-6f) return segA; // Avoid division by zero

        float t = (diff.x * lineDir.y - diff.y * lineDir.x) / cross;
        return segA + segDir * t;
    }
}
