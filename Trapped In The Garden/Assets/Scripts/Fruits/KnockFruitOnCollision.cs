using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KnockFruitOnCollision : MonoBehaviour
{
    private CsoundSender csoundSender;
    private Rigidbody rb;
    private ResetStartingPosition reset;

    private void Awake()
    {
        csoundSender = GetComponentInChildren<CsoundSender>();
        rb = GetComponent<Rigidbody>();
        reset = GetComponent<ResetStartingPosition>();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Hand"))
        {
            csoundSender.ToggleTrigger();
            rb.useGravity = true;
            reset.ResetPositionTimer();
            print("HAND COLLISION");
        }
        else if (collision.gameObject.CompareTag("Fruit"))
        {
            csoundSender.ToggleTrigger();
            reset.ResetPositionTimer();
        }
    }
}
