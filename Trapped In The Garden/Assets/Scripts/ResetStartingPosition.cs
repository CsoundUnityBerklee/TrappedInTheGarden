using System.Collections;
using UnityEngine;

public class ResetStartingPosition : MonoBehaviour
{
    private Vector3 startingPos;
    private float timer = 6.5f;

    // Start is called before the first frame update
    void Start()
    {
        startingPos = transform.position;

        ResetPositionTimer();
    }

    public void ResetPositionTimer()
    {
        StartCoroutine(Timer());
    }

    private void ResetPosition()
    {
        transform.position = startingPos;
    }

    private IEnumerator Timer()
    {
        yield return new WaitForSeconds(timer);
        ResetPosition();
    }
}
