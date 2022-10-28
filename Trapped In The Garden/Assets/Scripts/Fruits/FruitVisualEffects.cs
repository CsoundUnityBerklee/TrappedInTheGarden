using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FruitVisualEffects : MonoBehaviour
{
    private Material material;
    private TrailRenderer trail;
    public ParticleSystem particlesBurst, particlesLoop;
    private ParticleSystemRenderer particlesRendererBurst, particlesRendererLoop;

    // Start is called before the first frame update
    void Awake()
    {
        material = GetComponent<Renderer>().material;

        trail = GetComponent<TrailRenderer>();
        trail.material = material;

        particlesRendererBurst = particlesBurst.gameObject.GetComponent<ParticleSystemRenderer>();
        particlesRendererBurst.sharedMaterial = material;
        particlesRendererBurst.trailMaterial = material;

        particlesRendererLoop = particlesLoop.gameObject.GetComponent<ParticleSystemRenderer>();
        particlesRendererLoop.sharedMaterial = material;
        particlesRendererLoop.trailMaterial = material;
    }

    public void PlayParticlesBurst()
    {
        particlesBurst.gameObject.SetActive(true);  
        particlesBurst.Play();
    }

    public void PlayParticleLoop()
    {
        particlesLoop.gameObject.SetActive(true);
        particlesLoop.Play();
    }

    public void StopParticleLoop()
    {
        particlesLoop.Stop();
    }
}
