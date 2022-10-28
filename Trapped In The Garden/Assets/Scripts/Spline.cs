using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Spline Experiment
//Dream Machine
//Mateo Larrea 2021

//I followed a tutorial created by Cujo Sound

public class Spline : MonoBehaviour
{
    private Vector3[] splinePoint;
    private int splineCount;

    public bool debug_drawspline = true;




    // Start is called before the first frame update
    private void Start()
    {
        splineCount = transform.childCount;
        splinePoint = new Vector3[splineCount];

        for (int a = 0; a < splineCount; a++)
        {
            splinePoint[a] = transform.GetChild(a).position;
        }
        
    }

    // Update is called once per frame
    void Update()
    {
        if (debug_drawspline && splineCount > 1)
        {
            for (int b = 0; b < splineCount - 1; b++)
            {
                Debug.DrawLine(splinePoint[b], splinePoint[b + 1], Color.blue);
            }
        }
    }

    public Vector3 WhereOnSpline(Vector3 position)
    {
        int closestSplinePoint = GetClosestSplinePoint(position);


        if (closestSplinePoint == 0)
        {
            return splineSegment(splinePoint[0], splinePoint[1], position);
        }

        else if (closestSplinePoint == splineCount - 1)
        {
            return splineSegment(splinePoint[splineCount - 1], splinePoint[splineCount - 2], position);
        }

        else
        {
            Vector3 leftSeg = splineSegment(splinePoint[closestSplinePoint - 1], splinePoint[closestSplinePoint], position);
            Vector3 rightSeg = splineSegment(splinePoint[closestSplinePoint + 1], splinePoint[closestSplinePoint], position);

            if ((position - leftSeg).sqrMagnitude <= (position - rightSeg).sqrMagnitude)
            {
                return leftSeg;
            }
            else
            {
                return rightSeg;
            }
        }
    }

    private int GetClosestSplinePoint(Vector3 position)
    {
        int closestPoint = -1;
        float shortestDistance = 0.0f;

        for (int i = 0; i < splineCount; i++)
        {
            float sqrDistance = (splinePoint[i] - position).sqrMagnitude;

            if (shortestDistance == 0.0f || sqrDistance < shortestDistance)
            {
                shortestDistance = sqrDistance;
                closestPoint = i;
            }
        }

        return closestPoint;
    }

    public Vector3 splineSegment(Vector3 v1, Vector3 v2, Vector3 position)
    {
        Vector3 v1toPos = position - v1;
        Vector3 segDirection = (v2 - v1).normalized;

        float distanceFromV1 = Vector3.Dot(segDirection, v1toPos);

        if (distanceFromV1 < 0.0f)
        {
            return v1;

        }
        else if (distanceFromV1 * distanceFromV1 > (v2 - v1).sqrMagnitude)
        {
            return v2;
        }
        else
        {
            Vector3 fromV1 = segDirection * distanceFromV1;
            return v1 + fromV1;
        }
    }
}
