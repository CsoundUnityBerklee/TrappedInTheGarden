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
        if (other.gameObject.GetComponent<GravityZone>())
        {
            _source.Play();
            calculateVelocity = true;
        }
            
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
            float processedVel = velocity.magnitude;
            _source.pitch = Mathf.Clamp(processedVel, 0.1f, 2f);
        }
      
    }
}
