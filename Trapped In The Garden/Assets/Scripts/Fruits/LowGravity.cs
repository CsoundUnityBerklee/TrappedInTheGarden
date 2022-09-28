using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LowGravity : MonoBehaviour
{
    private Rigidbody rb;
    private Vector3 gravityVector = new Vector3(0, 7, 0);
    bool lowGravity = false;

    // Start is called before the first frame update
    void Awake()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!lowGravity) { return; }

        rb.AddForce(gravityVector, ForceMode.Force);
    }

    public void TurnOn()
    {
        lowGravity = true;
    }

    public void TurnOff()
    {
        lowGravity = false;
        rb.velocity = new Vector3(0, 0, 0);
        rb.angularVelocity = new Vector3(0, 0, 0);
    }

    public void Toggle()
    {
        if (lowGravity)
            TurnOff();
        else
            TurnOn();
    }
}
