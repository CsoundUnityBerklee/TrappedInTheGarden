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
    [SerializeField] bool currentlyPlaying = false;

    // Start is called before the first frame update
    void Start()
    {
        _source = GetComponent<AudioSource>();
        
    }

    void OnTriggerEnter(Collider other)
    {
<<<<<<< Updated upstream:Trapped In The Garden/Assets/SampleChanger.cs
        if (!_source.isPlaying)
=======
        if (!currentlyPlaying && other.gameObject.GetComponent<GravityMechanic>())
>>>>>>> Stashed changes:Trapped In The Garden/Assets/Scripts/SampleChanger.cs
        {
            if (other.gameObject.GetComponent<GravityMechanic>())
            {
                string objectName = other.gameObject.name;
                int.TryParse(objectName, out idNumber);

                _source.clip = _clips[idNumber];
                _source.Play();
<<<<<<< Updated upstream:Trapped In The Garden/Assets/SampleChanger.cs
            }
=======
                currentlyPlaying = true;
>>>>>>> Stashed changes:Trapped In The Garden/Assets/Scripts/SampleChanger.cs
        }
    }

    void OnTriggerExit(Collider other)
    {
<<<<<<< Updated upstream:Trapped In The Garden/Assets/SampleChanger.cs

=======
        if (other.gameObject.GetComponent<GravityMechanic>())
        {
            _source.Stop();
            currentlyPlaying = false;
        }
    }

    void PositionSamples()
    {
        for(int i = 0; i < _clips.Length; i++)
        {
            float posX = Random.Range(-60, 60);
            float posZ = Random.Range(-60, 60);

            Vector3 randomPos = new Vector3(posX, this.transform.position.y + 0.5f, posZ);
            GameObject newSample = Instantiate(sampleObjects[Random.Range(0, sampleObjects.Length)], randomPos, this.transform.rotation);

            newSample.name = i.ToString();

            // leave audio source ready 
            _source.playOnAwake = true;
            _source.loop = true;
    
        }
>>>>>>> Stashed changes:Trapped In The Garden/Assets/Scripts/SampleChanger.cs
    }
}
