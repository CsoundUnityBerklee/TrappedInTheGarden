using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum Direction
{
    positiveX, negativeX, positiveY, negativeY, positiveZ, negativeZ
}


public class Slider : MonoBehaviour
{
    [Header("Direction")]
    [Tooltip("Select the desired direction")]
    public Direction direction;


    // Variables to set the range of movement of the slider
    [SerializeField] float _min, _max;

    // Variable that will go to Csound
    float sliderDistance;

    // Lock X & Z
    [SerializeField] float xOriginalPos, zOrigialPos, yOriginalPos;

    // Csound
    [SerializeField] CsoundUnity csound;
    [SerializeField] string nameOfGameObject;
    [SerializeField] string [] parameters;
    [SerializeField] float [] _multiplier;



    // Property to update value only when it changes (opposed to every frame)
    public float SliderDistance
    {
        get
        {
            return sliderDistance;
        }
        set
        {
            if (sliderDistance == value) return;
            sliderDistance = value;
            if (OnVariableChange != null)
            {
                OnVariableChange(sliderDistance);

                for (int i = 0; i < parameters.Length; i++)
                {
                    csound.SetChannel(parameters[i], sliderDistance * _multiplier[i]);
                }
                 
            }   
            
        }
    }

    public delegate void OnVariableChangeDelegate(float newVal);
    public event OnVariableChangeDelegate OnVariableChange;




    private void Start()
    {
        if (nameOfGameObject == null)
            csound = GetComponent<CsoundUnity>();

        else
            csound = GameObject.Find(nameOfGameObject).GetComponent<CsoundUnity>();


        // Subscribing 
        OnVariableChange += VariableChangeHandler;

    }

    private void VariableChangeHandler(float newVal)
    { }


    // Update is called once per frame
    void Update()
    {
        float xValue = transform.localPosition.x;
        float yValue = transform.localPosition.y;
        float zValue = transform.localPosition.z;

        switch (direction)
        {

            case Direction.positiveX:
                
                SliderDistance = SliderValue(xValue, _min, _max, 0);
                break;

            case Direction.negativeX:
               
                SliderDistance = SliderValue(xValue, _max, _min, 0);
                break;

            case Direction.positiveY:

                SliderDistance = SliderValue(yValue, _min, _max, 1);
                break;

            case Direction.negativeY:

                SliderDistance = SliderValue(yValue, _max, _min, 1);
                break;


            case Direction.positiveZ:
                
                SliderDistance = SliderValue(zValue, _min, _max, 2);
                break;

            case Direction.negativeZ:
                
                SliderDistance = SliderValue(zValue, _max, _min, 2);
                break;

        }

    }


    float SliderValue(float axis, float min, float max, int xyz)
    {
        float rawValue = Mathf.Clamp(axis, min, max); // clamps slider values into the permitted range

        if (xyz == 0)
        {
            transform.localPosition = new Vector3(rawValue, yOriginalPos, zOrigialPos); // physical movement of slider
        }

        else if (xyz == 1)
        {
            transform.localPosition = new Vector3(xOriginalPos, rawValue, zOrigialPos); // physical movement of slider
        }

        else if (xyz == 2)
        {
            transform.localPosition = new Vector3(xOriginalPos, yOriginalPos, rawValue); // physical movement of slider
        }

        return 0.01f + Mathf.InverseLerp(_min, _max, rawValue);

    }
   
}
