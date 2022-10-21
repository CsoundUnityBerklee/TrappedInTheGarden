using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FruitVisualEffects : MonoBehaviour
{
    private Material material;
    private TrailRenderer trail;
    private ParticleSystem particles01;
    private ParticleSystemRenderer particlesRenderer01;

    // Start is called before the first frame update
    void Awake()
    {
        material = GetComponent<Renderer>().material;
        trail = GetComponent<TrailRenderer>();
        trail.material = material;

        particles01 = GetComponentInChildren<ParticleSystem>();
        particlesRenderer01 = GetComponentInChildren<ParticleSystemRenderer>();
        particlesRenderer01.sharedMaterial = material;
    }

    public void PlayParticles01()
    {
        particles01.Play();
    }

    public void StopParticles01()
    {
        particles01.Stop();
    }
}
