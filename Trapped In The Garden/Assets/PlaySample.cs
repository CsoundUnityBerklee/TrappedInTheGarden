using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlaySample : MonoBehaviour
{
    [SerializeField] AudioSource _source;

    // Start is called before the first frame update
    void Start()
    {
        _source = GetComponent<AudioSource>();
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<GravityZone>())
            _source.Play();
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<GravityZone>())
            _source.Stop();
    }
}
