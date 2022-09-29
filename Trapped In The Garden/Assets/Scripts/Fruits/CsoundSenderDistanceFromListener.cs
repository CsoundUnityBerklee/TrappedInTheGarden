using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CsoundSenderDistanceFromListener : MonoBehaviour
{
    public CsoundChannelRangeSO csoundChannelRange;
    public float minDistance, maxDistance;
    private float distance;
    private CsoundUnity csound;
    private GameObject listener;

    // Start is called before the first frame update
    void Awake()
    {
        csound = GetComponent<CsoundUnity>();
        listener = FindObjectOfType<AudioListener>().gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        distance = Vector3.Distance(gameObject.transform.position, listener.transform.position);
        CsoundMap.MapValueToChannelRangeInverted(csoundChannelRange, minDistance, maxDistance, distance, csound);
    }
}
