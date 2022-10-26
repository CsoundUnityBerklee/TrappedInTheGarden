using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GrabbingSoundDesign : MonoBehaviour
{

    [SerializeField] AudioClip[] grabbingClips;
    [SerializeField] AudioSource _source;


    // KEY
    // 0 = Sliders Selected
    // 1 = Sliders Released
    // Start is called before the first frame update
    void Start()
    {
        _source = GetComponent<AudioSource>();
    }

    public void PlayGrabbableSample(int numOfSample)
    {
        _source.clip = grabbingClips[numOfSample];
        _source.Play();
    }

}
