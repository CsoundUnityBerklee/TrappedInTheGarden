using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlantsBehaviour : MonoBehaviour
{

    // Growth
    [SerializeField] float scalingDuration = 5f; //Seconds
    [SerializeField] Vector3 targetScale = Vector3.one * .1f; //Target Scale
    Vector3 startingScale; //Starting Scale
    float interpolant = 0; //t for linear interpolation
    [SerializeField] bool isScaling = false;


    // Distance
    float distanceToCenter;
    [SerializeField] Transform _center;

    float distancetoCenter;


    // Trapped Section
    Garden garden;
    //public int trappedSection;

    [SerializeField] AudioSource _source;



    // Property to update value only when it changes (opposed to every frame)
    public float DistanceToCenter
    {
        get
        {
            return distancetoCenter;
        }
        set
        {
            if (distancetoCenter == value) return;
            distancetoCenter = value;
            if (OnVariableChange != null)
            {
                OnVariableChange(distancetoCenter);
                _source.pitch = distancetoCenter;

             

            }

        }
    }

    public delegate void OnVariableChangeDelegate(float newVal);
    public event OnVariableChangeDelegate OnVariableChange;

 
    void Start()
    {
        startingScale = this.transform.localScale;
        interpolant = 0;
        // Subscribing 
        OnVariableChange += VariableChangeHandler;


    //garden = GameObject.Find("Garden").GetComponent<Garden>();
}

private void VariableChangeHandler(float newVal)
{ }



void Update()
    {
        ScaleDown();
        
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            isScaling = true;
            
            _source.Play();
        }         
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            isScaling = false;
            
            transform.localScale = startingScale;
            _source.Stop();
            interpolant = 0; //restart
            //garden.StopTrapped(trappedSection);
        }
    }


    void ScaleDown()
    {
        if (isScaling)
        {


            DistanceToCenter = Vector3.Distance(gameObject.transform.position, _center.position) / 15;
            //time it takes from 0-1
            interpolant += Time.deltaTime / scalingDuration;

            // Lerp from startScale to targetScale (interpolant -> 0-1)
            Vector3 newScale = Vector3.Lerp(startingScale, targetScale, interpolant);

            transform.localScale = newScale;

            

            // Play Trapped

            //garden.TriggerTrapped(trappedSection);

            //optimization
            if (interpolant > 1)
            {
                isScaling = false;
                //garden.StopTrapped(trappedSection);
            }
        }
    }


}