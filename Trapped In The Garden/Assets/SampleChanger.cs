using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SampleChanger : MonoBehaviour
{
    // Changer Logic
    [SerializeField] AudioSource _source;
    [SerializeField] AudioClip[] _clips;
    int idNumber;

    // Sampler Maker
    [SerializeField] GameObject[] sampleObjects;

    // Start is called before the first frame update
    void Start()
    {
        _source = GetComponent<AudioSource>();
        
    }

    void OnTriggerEnter(Collider other)
    {
        if (!_source.isPlaying)
        {
            if (other.gameObject.GetComponent<GravityMechanic>())
            {
                string objectName = other.gameObject.name;
                int.TryParse(objectName, out idNumber);

                _source.clip = _clips[idNumber];
                _source.Play();
            }
        }
    }

    void OnTriggerExit(Collider other)
    {

    }
}
