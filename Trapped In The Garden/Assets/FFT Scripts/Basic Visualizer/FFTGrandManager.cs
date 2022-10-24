using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Basic FFT Example

[RequireComponent(typeof(AudioSource))]


public class FFTGrandManager : MonoBehaviour
{

    //|VARIABLES|

    //1) FFT INPUT
    AudioSource _audioSource;

    float[] samples = new float[512]; //Total # of Samples extracted

    float[][] _bandBuffer = new float[4][]; //****

    float[][] _bufferDecrease = new float[4][]; //****

    [SerializeField] float[] freqBand = new float[8]; //Distribution:
    //20-60 Hz - Sub Bass
    //60-250 - Bass
    //250-500 - Low Midrange
    //500-2kHz - Midrange
    //2-4kHz - Upper Midrange
    //4-6kHz - Presence
    //6-20kHz - Brilliance

    //2) FFT OUTPUT
    //Objects
    GameObject[][] _samplesAsObjects = new GameObject[4][]; //****

    [Tooltip("Initial transform.scale of objects/samples")]
    [Range(1, 20)] [SerializeField] int _startScale;

    [Range(50f, 200f)] [SerializeField] float _scale = 100; //Determines the variation in Y of the affected objects

    //Buffer
    [Tooltip("Makes movement more continous")]
    [SerializeField] bool UseBuffer = true; //When to go into Buffer mode

    [Range(0.05f, 0.0005f)] [SerializeField] float bufferSpeedA; //Delta

    [Range(0.9f, 1.5f)] [SerializeField] float bufferSpeedB; //Delta

    //Objects and Parameters
    [Tooltip("Must be the same number than the size of _samplesAsObjects[x][]")]
    [SerializeField] int[] numberOfSamples; //How many object per group (Samples) ****

    [Tooltip("Must be the same number than the size of _samplesAsObjects[x][]")]
    [SerializeField] GameObject[] SamplePrefabs; //Object that will conform each group ****

    [Tooltip("Must be the same number than the size of _samplesAsObjects[x][]")]
    [SerializeField] int[] Distance; //Distance from the object containing the script ****
    


    // Start is called before the first frame update
    void Start()
    {

        _audioSource = GetComponent<AudioSource>();

        ////Assigns how many objects/samples need to be created/added for x numbers of groups
        for (int a = 0; a < _samplesAsObjects.Length; a++)
        {
            _samplesAsObjects[a] = new GameObject[numberOfSamples[a]]; 
            _bandBuffer[a] = new float[numberOfSamples[a]];
            _bufferDecrease[a] = new float[numberOfSamples[a]]; 

        }

        //Initialize Buffer Parameters
        bufferSpeedA = 0.02f;
        bufferSpeedB = 1.08f;

        //Environment is created
        AssignGroups(); 

    }

    // Update is called once per frame
    void Update()
    {
        GetSpectrumAudioSource(); //Gets the Data

        MakeFrequencyBands(); //Splits frequencies into groups (based on value)

        ScalingMovement(); //Makes objects react to the two previous methods

        BandBuffer(); //Does the same than ScalingMovement() but in a more continous way
    }

    //Custom Funcs/Methods

    void GetSpectrumAudioSource()
    {
        _audioSource.GetSpectrumData(samples, 0, FFTWindow.Blackman);
    }

    void MakeFrequencyBands()
    {

        int count = 0;

        for (int b = 0; b < 8; b++)
        {
            float average = 0;
            int sampleCount = (int)Mathf.Pow(2, b) * 2; // --> 2, 4, 8, 16, 32,....., 256

            if (b == 7)
            {
                sampleCount += 2; // to get 512 intead of 510
            }

            for (int c = 0; c < sampleCount; c++)
            {
                average += samples[count] * (count + 1);
                count++;
            }

            average /= count;

            freqBand[b] = average * 10;

        }

    }


    void AssignGroups()
    {
        for (int d = 0; d < _samplesAsObjects.Length; d++)
        {
            for (int e = 0; e < numberOfSamples[d]; e++)
            {
                //Create the object
                GameObject copiedObject = (GameObject)Instantiate(SamplePrefabs[d]); //Copies sampleObjectPrefab
                copiedObject.transform.position = this.transform.position; //Assigns it to position of the object where the script is attached
                copiedObject.transform.parent = this.transform;
                copiedObject.name = "Object #" + e; //Changes name and adds number to copy

                //Position the object
                float EulerY;
                this.transform.eulerAngles = new Vector3(0, EulerY = (float)-360 / numberOfSamples[d] * e, 0); //Euler Y = 360/# of objects in group
                
                copiedObject.transform.position = Vector3.forward * Distance[d]; 
                _samplesAsObjects[d][e] = copiedObject;

            }
        }
    }

    void ScalingMovement()
    {
        for (int f = 0; f < _samplesAsObjects.Length; f++)
        {
            for (int g = 0; g < numberOfSamples[f]; g++)
            {
                if (_samplesAsObjects[f] != null)
                {
                    if (UseBuffer == true)
                    {
                        _samplesAsObjects[f][g].transform.localScale = new Vector3(10, (_bandBuffer[f][g] * 10) + _startScale, 10); 
                    }
                    else
                    {
                        _samplesAsObjects[f][g].transform.localScale = new Vector3(10, (samples[g] * _scale) + _startScale, 10);
                    }
                    
                }
            }

        }

    }

    void BandBuffer()
    {
        for (int h = 0; h < _samplesAsObjects.Length; h++)
        {
            for (int i = 0; i < numberOfSamples[h]; i++)
            {

                if (freqBand[h] > _bandBuffer[h][i])
                {

                    _bandBuffer[h][i] = freqBand[h];
                    _bufferDecrease[h][i] = bufferSpeedA;
                }

                if (freqBand[h] < _bandBuffer[h][i])
                {
                    _bandBuffer[h][i] -= _bufferDecrease[h][i];
                    _bufferDecrease[h][i] *= bufferSpeedB; 

                }
            }
        }
    }

}
