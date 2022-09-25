using System.Collections;
using UnityEngine;

public class ResetStartingPosition : MonoBehaviour
{
    private CsoundSender csoundSender;
    private Vector3 startingPos;
    private float timer = 10f;
    private Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        startingPos = transform.position;
        csoundSender = GetComponentInChildren<CsoundSender>();
        ResetPositionTimer();
    }

    public void ResetPositionTimer()
    {
        StartCoroutine(Timer());
    }

    private IEnumerator Timer()
    {
        yield return new WaitForSeconds(timer);
        ResetObject();
    }

    private void ResetObject()
    {
        //Reset rigidbody
        rb.velocity = new Vector3(0, 0, 0);
        rb.angularVelocity = new Vector3(0, 0, 0);
        rb.useGravity = false;
        //Reset CsoundUnity
        csoundSender.ResetPreset();
        csoundSender.SetChannelValue(1); //turns off retrigger
        //Reset transform
        transform.position = startingPos;
    }
}
