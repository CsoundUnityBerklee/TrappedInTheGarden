using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StarManager : MonoBehaviour
{

    [SerializeField] AudioClip[] _clips;
    AudioSource _source;
    [SerializeField] GameObject[] _stars;
    [SerializeField] int numberOfStars;

    // Start is called before the first frame update
    void Start()
    {
        InstantiateStars();
    }

    void InstantiateStars()
    {
        for (int i = 0; i < numberOfStars; i++)
        {
            float X = Random.Range(-20, 20);
            float Y = Random.Range(0, 15);
            float Z = Random.Range(-20, 20);

            GameObject CopiedObject = Instantiate(_stars[(int)Random.Range(0, _stars.Length)], new Vector3(X, Y, Z), Quaternion.identity);

            CopiedObject.GetComponent<AudioSource>().clip = _clips[Random.Range(0, _clips.Length)];

        }
        
    }

}
