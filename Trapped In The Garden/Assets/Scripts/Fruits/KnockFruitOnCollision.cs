using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KnockFruitOnCollision : MonoBehaviour
{
    private CsoundSender csoundSender;
    private Rigidbody rb;
    private ResetStartingPosition reset;

    private DebugCollision debug;

    private void Awake()
    {
        csoundSender = GetComponentInChildren<CsoundSender>();
        rb = GetComponent<Rigidbody>();
        debug = FindObjectOfType<DebugCollision>();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Hand"))
        {
            csoundSender.ToggleTrigger();
            rb.useGravity = true;
            reset.ResetPositionTimer();
        }
        else if (collision.gameObject.CompareTag("Fruit"))
        {
            csoundSender.ToggleTrigger();
            reset.ResetPositionTimer();
        }
    }
}
