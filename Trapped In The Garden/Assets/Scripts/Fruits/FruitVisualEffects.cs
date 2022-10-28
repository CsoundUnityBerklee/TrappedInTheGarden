using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FruitVisualEffects : MonoBehaviour
{
    private Material material;
    private TrailRenderer trail;
    public ParticleSystem particlesBurst, particlesLoop;
    private ParticleSystemRenderer particlesRendererBurst, particlesRendererLoop;

    //Rotation
    private CsoundTransformAndPhysicsSender csoundPhysics;
    private float minMaxParticles = 4f, maxMaxParticles = 100f;
    private float minSpeed = 0.3f, maxSpeed = 1.5f;

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

        csoundPhysics = GetComponentInChildren<CsoundTransformAndPhysicsSender>();
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

    public void TieToRotation()
    {
        var main = particlesLoop.main;
        //Max particles
        float scaledMaxParticles = CsoundMap.ScaleFloat(0, 360, minMaxParticles, maxMaxParticles, csoundPhysics.RotationSender.zAxisValue);
        main.maxParticles = (int)scaledMaxParticles;
        //Playback speed
        float scaledSpeed = CsoundMap.ScaleFloat(0, 360, minSpeed, maxSpeed, csoundPhysics.RotationSender.zAxisValue);
        main.simulationSpeed = scaledSpeed;
    }
}
