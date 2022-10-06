using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GravityMechanic : MonoBehaviour
{
    Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<GravityZone>())
        {
            rb.useGravity = true;
            rb.isKinematic = true;
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<GravityZone>())
        {
            rb.useGravity = false;
            rb.isKinematic = false;
        }
    }


}
