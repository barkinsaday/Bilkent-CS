using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Fortune's Sweep Line Voronoi Generator (Animation Ready)
/// </summary>
public class FortuneVoronoiGenerator
{
    public class VoronoiEdge
    {
        public Vector2 start;
        public Vector2? end; // null if still open edge
        public Vector2 direction;
        public Vector2 siteA, siteB;
    }

    public class Event
    {
        public float y;
        public Vector2 position;
        public bool isSiteEvent;
        public Arc associatedArc; // For circle events
    }

    public class Arc
    {
        public Vector2 site;
        public Event circleEvent; // Pending circle event, if any
        public Arc prev, next;    // Linked list for beachline
        public Breakpoint leftBreakpoint;
        public Breakpoint rightBreakpoint;
    }
    public class Breakpoint
    {
        public Vector2 siteA, siteB;
        public Arc leftArc, rightArc;
        public VoronoiEdge edge;
    }


    private PriorityQueue<Event> eventQueue = new PriorityQueue<Event>();
    private Arc beachlineRoot = null;
    private List<VoronoiEdge> edges = new List<VoronoiEdge>();

    private Rect boundingBox;

    // Public API
    public static FortuneVoronoiGeneratorResult ComputeVoronoi(List<Vector2> sites, Rect bounds)
    {
        Debug.LogError("Fortune Algo Called");
        var fortune = new FortuneVoronoiGenerator();
        return fortune.Run(sites, bounds);
    }

    private FortuneVoronoiGeneratorResult Run(List<Vector2> sites, Rect bounds)
    {
        boundingBox = bounds;

        // Step 1: Initialize Event Queue with Site Events
        foreach (var site in sites)
            eventQueue.Enqueue(new Event { y = site.y, position = site, isSiteEvent = true });

        // Step 2: Process Events
        while (eventQueue.Count > 0)
        {
            Event e = eventQueue.Dequeue();

            if (e.isSiteEvent)
                HandleSiteEvent(e);
            else
                HandleCircleEvent(e);
        }

        // Step 3: Close unfinished edges
        FinalizeEdges();

        // Step 4: Return result for rendering
        return BuildResult();
    }

    private void HandleSiteEvent(Event e)
    {
        Vector2 site = e.position;

        if (beachlineRoot == null)
        {
            beachlineRoot = new Arc { site = site };
            return;
        }

        Arc arc = GetArcAbove(site);

        if (arc.circleEvent != null)
        {
            eventQueue.Remove(arc.circleEvent);
            arc.circleEvent = null;
        }

        // Create new arcs: left (existing arc), newArc (new site), right (copy of arc.site)
        Arc newArc = new Arc { site = site };
        Arc arcRight = new Arc { site = arc.site };

        arcRight.next = arc.next;
        if (arc.next != null) arc.next.prev = arcRight;

        arc.next = newArc;
        newArc.prev = arc;
        newArc.next = arcRight;
        arcRight.prev = newArc;

        // Create new breakpoints & edges
        Breakpoint leftBreakpoint = new Breakpoint
        {
            siteA = arc.site,
            siteB = site,
            leftArc = arc,
            rightArc = newArc
        };
        VoronoiEdge leftEdge = new VoronoiEdge
        {
            start = ComputeBreakpoint(arc.site, site, e.position.y),
            direction = GetEdgeDirection(arc.site, site),
            siteA = arc.site,
            siteB = site
        };
        leftBreakpoint.edge = leftEdge;
        edges.Add(leftEdge);

        Breakpoint rightBreakpoint = new Breakpoint
        {
            siteA = site,
            siteB = arcRight.site,
            leftArc = newArc,
            rightArc = arcRight
        };
        VoronoiEdge rightEdge = new VoronoiEdge
        {
            start = ComputeBreakpoint(site, arcRight.site, e.position.y),
            direction = GetEdgeDirection(site, arcRight.site),
            siteA = site,
            siteB = arcRight.site
        };
        rightBreakpoint.edge = rightEdge;
        edges.Add(rightEdge);

        // Update arc pointers to their respective breakpoints
        arc.rightBreakpoint = leftBreakpoint;
        newArc.leftBreakpoint = leftBreakpoint;

        newArc.rightBreakpoint = rightBreakpoint;
        arcRight.leftBreakpoint = rightBreakpoint;

        // Re-evaluate circle events
        CheckCircleEvent(arc);
        CheckCircleEvent(arcRight);
        CheckCircleEvent(newArc);
    }

    private void HandleCircleEvent(Event e)
    {
        Arc arc = e.associatedArc;
        Vector2 vertex = e.position;

        // Finalize edges of disappearing arc’s breakpoints
        if (arc.leftBreakpoint != null)
            arc.leftBreakpoint.edge.end = vertex;

        if (arc.rightBreakpoint != null)
            arc.rightBreakpoint.edge.end = vertex;

        // Remove arc from beachline
        if (arc.prev != null) arc.prev.next = arc.next;
        if (arc.next != null) arc.next.prev = arc.prev;

        // Reconnect breakpoints
        if (arc.prev != null && arc.next != null)
        {
            Breakpoint newBreakpoint = new Breakpoint
            {
                siteA = arc.prev.site,
                siteB = arc.next.site,
                leftArc = arc.prev,
                rightArc = arc.next
            };

            VoronoiEdge newEdge = new VoronoiEdge
            {
                start = vertex,
                direction = GetEdgeDirection(arc.prev.site, arc.next.site),
                siteA = arc.prev.site,
                siteB = arc.next.site
            };
            newBreakpoint.edge = newEdge;
            edges.Add(newEdge);

            arc.prev.rightBreakpoint = newBreakpoint;
            arc.next.leftBreakpoint = newBreakpoint;
        }

        // Invalidate neighbors' circle events
        if (arc.prev != null && arc.prev.circleEvent != null)
        {
            eventQueue.Remove(arc.prev.circleEvent);
            arc.prev.circleEvent = null;
        }
        if (arc.next != null && arc.next.circleEvent != null)
        {
            eventQueue.Remove(arc.next.circleEvent);
            arc.next.circleEvent = null;
        }

        // Re-check circle events
        if (arc.prev != null) CheckCircleEvent(arc.prev);
        if (arc.next != null) CheckCircleEvent(arc.next);
    }




    private Vector2 GetPerpendicularDirection(Vector2 siteA, Vector2 siteB)
    {
        Vector2 delta = siteB - siteA;
        Vector2 perpendicular = new Vector2(-delta.y, delta.x); // 90 degree rotation
        return perpendicular.normalized;
    }

    private Vector2 ComputeBreakpoint(Vector2 leftSite, Vector2 rightSite, float sweeplineY)
    {
        // Simplified parabola intersection for initial positioning
        // For visualization, a midpoint is often good enough
        return (leftSite + rightSite) / 2f;
    }




    private void CheckCircleEvent(Arc arc)
    {
        if (arc.prev == null || arc.next == null)
            return;

        Vector2 a = arc.prev.site;
        Vector2 b = arc.site;
        Vector2 c = arc.next.site;

        // Check for circle event: sites must form a counter-clockwise turn
        if (CrossProduct(a, b, c) >= 0)
            return;

        // Compute circle center through circumcircle
        Vector2 circumcenter = CircumcircleCenter(a, b, c);
        float radius = Vector2.Distance(circumcenter, b);

        // The lowest point of the circle defines the event
        Vector2 eventPoint = new Vector2(circumcenter.x, circumcenter.y - radius);

        // Ignore if below current sweepline
        if (eventPoint.y >= b.y)
            return;

        Event circleEvent = new Event
        {
            y = eventPoint.y,
            position = eventPoint,
            isSiteEvent = false,
            associatedArc = arc
        };

        arc.circleEvent = circleEvent;
        eventQueue.Enqueue(circleEvent);
    }

    private void FinalizeEdges()
    {
        foreach (var edge in edges)
        {
            if (edge.end.HasValue) continue; // Already finalized by circle event

            Vector2 intersection = ComputeBoundingBoxIntersection(edge.start, edge.direction);

            edge.end = intersection;
        }
    }


    private Vector2 ComputeBoundingBoxIntersection(Vector2 start, Vector2 direction)
    {
        direction.Normalize();

        float tMin = float.PositiveInfinity;
        Vector2 result = start;

        Rect bounds = boundingBox;

        // Left boundary (x = bounds.xMin)
        if (Mathf.Abs(direction.x) > 1e-8f)
        {
            float t = (bounds.xMin - start.x) / direction.x;
            if (t > 0)
            {
                float y = start.y + t * direction.y;
                if (y >= bounds.yMin && y <= bounds.yMax && t < tMin)
                {
                    tMin = t;
                    result = new Vector2(bounds.xMin, y);
                }
            }
        }

        // Right boundary (x = bounds.xMax)
        if (Mathf.Abs(direction.x) > 1e-8f)
        {
            float t = (bounds.xMax - start.x) / direction.x;
            if (t > 0)
            {
                float y = start.y + t * direction.y;
                if (y >= bounds.yMin && y <= bounds.yMax && t < tMin)
                {
                    tMin = t;
                    result = new Vector2(bounds.xMax, y);
                }
            }
        }

        // Bottom boundary (y = bounds.yMin)
        if (Mathf.Abs(direction.y) > 1e-8f)
        {
            float t = (bounds.yMin - start.y) / direction.y;
            if (t > 0)
            {
                float x = start.x + t * direction.x;
                if (x >= bounds.xMin && x <= bounds.xMax && t < tMin)
                {
                    tMin = t;
                    result = new Vector2(x, bounds.yMin);
                }
            }
        }

        // Top boundary (y = bounds.yMax)
        if (Mathf.Abs(direction.y) > 1e-8f)
        {
            float t = (bounds.yMax - start.y) / direction.y;
            if (t > 0)
            {
                float x = start.x + t * direction.x;
                if (x >= bounds.xMin && x <= bounds.xMax && t < tMin)
                {
                    tMin = t;
                    result = new Vector2(x, bounds.yMax);
                }
            }
        }

        return result;
    }


    private Vector2 LineIntersect(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2)//optional
    {
        Vector2 r = p2 - p1;
        Vector2 s = q2 - q1;
        float rxs = r.x * s.y - r.y * s.x;

        if (Mathf.Abs(rxs) < 1e-8f)
            return p1; // Parallel fallback

        float t = ((q1 - p1).x * s.y - (q1 - p1).y * s.x) / rxs;
        return p1 + t * r;
    }

    private Vector2 GetEdgeDirection(Vector2 siteA, Vector2 siteB)
    {
        Vector2 delta = siteB - siteA;
        Vector2 perpendicular = new Vector2(-delta.y, delta.x); // Perpendicular bisector
        return perpendicular.normalized;
    }



    private Arc GetArcAbove(Vector2 point)
    {
        Arc arc = beachlineRoot;
        float directrixY = point.y;

        while (arc != null)
        {
            Vector2 left = Vector2.zero;
            Vector2 right = Vector2.zero;

            if (arc.prev != null)
                left = GetBreakpoint(arc.prev, arc, directrixY);
            else
                left = new Vector2(float.NegativeInfinity, 0);

            if (arc.next != null)
                right = GetBreakpoint(arc, arc.next, directrixY);
            else
                right = new Vector2(float.PositiveInfinity, 0);

            if (point.x >= left.x && point.x <= right.x)
                return arc;

            arc = arc.next;
        }

        return null;
    }

    private Vector2 GetBreakpoint(Arc leftArc, Arc rightArc, float directrixY)
    {
        Vector2 p = leftArc.site;
        Vector2 r = rightArc.site;

        float dp = 2 * (p.y - directrixY);
        float dr = 2 * (r.y - directrixY);

        if (dp == dr)
            return new Vector2((p.x + r.x) / 2, 0);

        float a = 1 / dp - 1 / dr;
        float b = -2 * (p.x / dp - r.x / dr);
        float c = (p.x * p.x + p.y * p.y - directrixY * directrixY) / dp - (r.x * r.x + r.y * r.y - directrixY * directrixY) / dr;

        float disc = b * b - 4 * a * c;
        float x = (-b + Mathf.Sqrt(disc)) / (2 * a);

        return new Vector2(x, 0);
    }

    // Helper to compute circumcircle center
    private Vector2 CircumcircleCenter(Vector2 a, Vector2 b, Vector2 c)
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

    private float CrossProduct(Vector2 a, Vector2 b, Vector2 c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    

    private FortuneVoronoiGeneratorResult BuildResult()
    {
        // Convert edges to final regions if needed (optional for now)
        // For your system, just return edges
        return new FortuneVoronoiGeneratorResult { edges = edges };
    }
 
   
    // Result Wrapper Class
    public class FortuneVoronoiGeneratorResult
    {
        public List<VoronoiEdge> edges;
    }

    // Simple Priority Queue Implementation (min-heap by y)
    private class PriorityQueue<T> where T : Event
    {
        private List<T> data = new List<T>();

        public int Count => data.Count;

        public void Enqueue(T item)
        {
            data.Add(item);
            data.Sort((a, b) => a.y.CompareTo(b.y)); // min-heap behavior (lowest y first)
        }

        public T Dequeue()
        {
            T first = data[0];
            data.RemoveAt(0);
            return first;
        }

        public void Remove(T item)
        {
            data.Remove(item); // Simple O(n) removal
        }
    }

}
