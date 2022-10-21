using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FFTSelector : MonoBehaviour
{
    [SerializeField] CsoundUnity csound;
    [SerializeField] string nameOfGameObject;

    // Start is called before the first frame update
    void Start()
    {
        csound = GameObject.Find(nameOfGameObject).GetComponent<CsoundUnity>();
    }

    public void SetFFT(int fftSize)
    {
        csound.SetChannel("att_table", fftSize);
    }

}
