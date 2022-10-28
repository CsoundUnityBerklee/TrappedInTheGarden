using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sequencer : MonoBehaviour
{
    [SerializeField] AudioSource _source;
    [SerializeField] AudioClip[] _clips;
    [SerializeField] string[] _tags;

    // Start is called before the first frame update
    void Start()
    {
        _source = GameObject.Find("Sequencer Area / Logic").GetComponent<AudioSource>();


    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag(_tags[0]))
        {
            _source.clip = _clips[0];
            _source.volume = Vector3.Distance(other.transform.position, _source.transform.position)/2f;
            _source.Play();
        }
        else if (other.gameObject.CompareTag(_tags[1]))
        {
            _source.clip = _clips[0];
            _source.volume = Vector3.Distance(other.transform.position, _source.transform.position) / 2f;
            _source.Play();
        }
        else if (other.gameObject.CompareTag(_tags[2]))
        {
            _source.clip = _clips[2];
            _source.volume = Vector3.Distance(other.transform.position, _source.transform.position) / 2f;
            _source.Play();
        }
        else if (other.gameObject.CompareTag(_tags[3]))
        {
            _source.clip = _clips[3];
            _source.volume = Vector3.Distance(other.transform.position, _source.transform.position) / 2f;
            _source.Play();
        }
        else
        {
            _source.clip = _clips[4];
            _source.volume = Vector3.Distance(other.transform.position, _source.transform.position) / 2f;
            _source.Play();
        }
    }



}
