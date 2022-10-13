using System.Collections;
using UnityEngine;

public class ResetStartingPosition : MonoBehaviour
{
    private CsoundUnity csoundUnity;
    private Vector3 startingPos;
    private float timer = 5f;
    private Rigidbody rb;
    private LowGravity lowGravity;
    private float speed = 5f;
    private float speedIncrement = 0.35f;
    private bool moveTowardsStartingPos = false;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        startingPos = transform.position;
        csoundUnity = GetComponentInChildren<CsoundUnity>();
        lowGravity = GetComponent<LowGravity>();
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
        moveTowardsStartingPos = true;

        //Reset gravity
        lowGravity.TurnOff();
        //Reset rigidbody
        rb.velocity = new Vector3(0, 0, 0);
        rb.angularVelocity = new Vector3(0, 0, 0);

        rb.useGravity = false;
    }

    private void Update()
    {
        if (moveTowardsStartingPos)
        {
            MoveTowardsStartingPosition();
        }
    }

    private void MoveTowardsStartingPosition()
    {
        if (transform.position == startingPos)
        {
            moveTowardsStartingPos = false;
            //Reset CsoundUnity
            csoundUnity.SetChannel("reTrigger", 0); //turns off reTrigger
        }

        speed += speedIncrement;
        transform.position = Vector3.MoveTowards(transform.position, startingPos, speed * Time.deltaTime);
    }
}
