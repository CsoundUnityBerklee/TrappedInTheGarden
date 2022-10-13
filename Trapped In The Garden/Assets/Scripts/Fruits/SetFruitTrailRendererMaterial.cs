using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetFruitTrailRendererMaterial : MonoBehaviour
{
    private Material material;
    private TrailRenderer trail;

    // Start is called before the first frame update
    void Awake()
    {
        material = GetComponent<Renderer>().material;
        trail = GetComponent<TrailRenderer>();
        trail.material = material;
    }
}
