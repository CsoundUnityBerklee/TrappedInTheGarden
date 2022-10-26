using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SampleSelector : MonoBehaviour
{
    [SerializeField] CsoundUnity [] _csound;
    [SerializeField] string [] _objects;
    [Tooltip("Ids must go from 1 to the number of samples that are present inside the csd")]
    [SerializeField] int _id;


    private void Start()
    {
        //_csound = GetComponent<CsoundUnity>();
        for (int i = 0; i < 2; i++)
        {
            _csound[i] = GameObject.Find(_objects[i]).GetComponent<CsoundUnity>();
            _csound[i].SetChannel("dur", 500);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<SampleHolderPVS>())
        {
            
            _csound[0].SetChannel("sound", _id); // Select correct sound
            _csound[0].SetChannel("trigger", _csound[0].GetChannel("trigger") == 1 ? 0 : 1);
        }
        else if (other.gameObject.GetComponent<SampleHolderFlooper>())
        {
            _csound[1].SetChannel("sound", _id); // Select correct sound
            _csound[1].SetChannel("trigger", _csound[1].GetChannel("trigger") == 1 ? 0 : 1);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<SampleHolderPVS>())
        {
            
            _csound[0].SetChannel("sound", _id); // Select correct sound
            _csound[0].SetChannel("stop", _csound[0].GetChannel("stop") == 1 ? 0 : 1);
        }

        else if (other.gameObject.GetComponent<SampleHolderFlooper>())
        {
            _csound[1].SetChannel("sound", _id); // Select correct sound
            _csound[1].SetChannel("stop", _csound[1].GetChannel("stop") == 1 ? 0 : 1);

        }
    }
}
