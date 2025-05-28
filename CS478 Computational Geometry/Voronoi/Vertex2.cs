using MIConvexHull;
using UnityEngine;

public class Vertex2 : IVertex
{
    public double[] Position { get; set; }

    public Vertex2(Vector2 v)
    {
        Position = new double[] { v.x, v.y };
    }

    public Vector2 ToVector2() => new Vector2((float)Position[0], (float)Position[1]);
}
