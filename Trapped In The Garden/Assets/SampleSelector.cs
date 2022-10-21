using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SampleSelector : MonoBehaviour
{
    [SerializeField] CsoundUnity _csound;
    [Tooltip("Ids must go from 1 to the number of samples that are present inside the csd")]
    [SerializeField] int _id;


    private void Start()
    {
        //_csound = GetComponent<CsoundUnity>();
        _csound.SetChannel("dur", 500);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<SampleHolder>())
        {
            Debug.Log("Entered");
            _csound.SetChannel("sound", _id); // Select correct sound
            _csound.SetChannel("trigger", _csound.GetChannel("trigger") == 1 ? 0 : 1);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<SampleHolder>())
        {
            Debug.Log("ByeBye!");
            _csound.SetChannel("sound", _id); // Select correct sound
            _csound.SetChannel("stop", _csound.GetChannel("stop") == 1 ? 0 : 1);
        }
    }
}
