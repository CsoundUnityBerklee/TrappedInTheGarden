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
        PositionSamples();
        
    }

    void OnTriggerEnter(Collider other)
    {
        if (!_source.isPlaying && other.gameObject.GetComponent<GravityMechanic>())
        {
                string objectName = other.gameObject.name;
                int.TryParse(objectName, out idNumber);

                _source.clip = _clips[idNumber];
                Debug.Log("Hola");
                _source.Play();
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<GravityMechanic>())
        {
            _source.Stop();
        }
    }

    void PositionSamples()
    {
        for(int i = 0; i < _clips.Length; i++)
        {
            float posX = Random.Range(-60, 60);
            float posZ = Random.Range(-60, 60);

            Vector3 randomPos = new Vector3(posX, this.transform.position.y, posZ);
            GameObject newSample = Instantiate(sampleObjects[Random.Range(0, sampleObjects.Length)], randomPos, this.transform.rotation);

            newSample.name = i.ToString();
        }
    }
}
