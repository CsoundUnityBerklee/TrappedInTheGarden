using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Slider : MonoBehaviour
{
    
    // Variables to set the range of movement of the slider
    [SerializeField] float _min, _max;

    // Variable that will be sent to RealtimeRotatingObject
    float elevation;

    // Lock X & Z
    [SerializeField] float xOriginalPos, zOrigialPos;



    // Csound
    [SerializeField] CsoundUnity csound;
    
    [SerializeField] string parameter;
    [SerializeField] float _offset;

    // Property to update value only when it changes (opposed to every frame)
    public float Elevation
    {
        get
        {
            return elevation;
        }
        set
        {
            if (elevation == value) return;
            elevation = value;
            if (OnVariableChange != null)
            {
                OnVariableChange(elevation);
                csound.SetChannel(parameter, elevation); 
            }   
            
        }
    }

    public delegate void OnVariableChangeDelegate(float newVal);
    public event OnVariableChangeDelegate OnVariableChange;




    private void Start()
    {
        csound = GameObject.Find("Sample Player").GetComponent<CsoundUnity>();



        // Subscribing 
        OnVariableChange += VariableChangeHandler;

       


    }

    private void VariableChangeHandler(float newVal)
    { }


    // Update is called once per frame
    void Update()
    {

       float rawValue = Mathf.Clamp(transform.position.y, _min, _max); // clamps slider values into the permitted range

        transform.position = new Vector3(xOriginalPos, rawValue, zOrigialPos); // physical movement of slider

        Elevation = 0.01f + Mathf.InverseLerp(_min, _max, rawValue) * _offset; 

    }
}
