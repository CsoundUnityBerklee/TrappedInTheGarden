using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LowGravity : MonoBehaviour
{
    private Rigidbody rb;
    bool lowGravity = false;

    // Start is called before the first frame update
    void Awake()
    {
        rb = GetComponent<Rigidbody>();
    }
    public void TurnOn()
    {
        lowGravity = true;
        StartCoroutine(DisableRbGravity());
    }

    public void TurnOff()
    {
        lowGravity = false;
        rb.useGravity = false;
        //rb.velocity = new Vector3(0, 0, 0);
        //rb.angularVelocity = new Vector3(0, 0, 0);
    }

    public void Toggle()
    {
        if (lowGravity)
            TurnOff();
        else
            TurnOn();
    }

    private IEnumerator DisableRbGravity()
    {
        yield return new WaitForSeconds(0.2f);
        rb.useGravity = false;
    }
}