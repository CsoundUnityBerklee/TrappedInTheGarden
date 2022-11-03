using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VelocityToPitch : MonoBehaviour
{
    [SerializeField] AudioSource _source;
    [SerializeField] Rigidbody rb;

    bool calculateVelocity;

    // Start is called before the first frame update
    void Start()
    {
        _source = GetComponent<AudioSource>();
        rb = GetComponent<Rigidbody>();

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<GetControllerButtonValues>())
            _source.Play();

        if (other.gameObject.GetComponent<GravityZone>())
            calculateVelocity = true;



            
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<GravityZone>())
        {
            calculateVelocity = false;
            _source.Stop();
        }
           
    }

    private void Update()
    {
        if (calculateVelocity)
        {
            Vector3 velocity = rb.velocity;
            float processedVel = Map(velocity.magnitude, 0f, 5f, 0.5f, 3.5f);
            _source.pitch = Mathf.Clamp(processedVel, -2f, 2f);
        }
      
    }

    // Map Function
    float Map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

}
