using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CsoundSenderDistanceFromListener : MonoBehaviour
{
    private string channelName = "macro1";
    private float startingValue;
    private float minOffset = 10;
    public float minDistance, maxDistance;
    private float distance;
    private CsoundUnity csound;
    private GameObject listener;

    private bool canUpdate = false;

    private float distanceTest;

    // Start is called before the first frame update
    void Awake()
    {
        csound = GetComponent<CsoundUnity>();
        listener = FindObjectOfType<AudioListener>().gameObject;
    }

    public void Initialize()
    {
        startingValue = (float)csound.GetChannel(channelName);
    }

    // Update is called once per frame
    void Update()
    {
        if (!canUpdate) { return; }

        distance = Vector3.Distance(gameObject.transform.position, listener.transform.position);
        float scaled01 = Mathf.Clamp(CsoundMap.ScaleFloat(minDistance, maxDistance, 0, 1, distance), 0, 1);
        float newValue = Mathf.Clamp(startingValue - (scaled01 * 0.5f), 0.1f, 3);
        csound.SetChannel(channelName, newValue);
    }

    public void TurnOn()
    {
        Initialize();
        canUpdate = true;
    }

    public void TurnOff()
    {
        canUpdate = false;
    }
}
