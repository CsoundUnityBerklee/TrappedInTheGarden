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
    [SerializeField] bool calculatingDistance = false;


    // Trapped Section
    Garden garden;
    public int trappedSection;



    void Start()
    {
        startingScale = this.transform.localScale;
        interpolant = 0;

        garden = GameObject.Find("Garden").GetComponent<Garden>();

    }



    void Update()
    {
        ScaleDown();
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            isScaling = true;
            calculatingDistance = true;
        }         
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            isScaling = false;
            calculatingDistance = false;
            transform.localScale = startingScale;
            interpolant = 0; //restart
            garden.StopTrapped(trappedSection);
        }
    }


    void ScaleDown()
    {
        if (isScaling)
        {
            //time it takes from 0-1
            interpolant += Time.deltaTime / scalingDuration;

            // Lerp from startScale to targetScale (interpolant -> 0-1)
            Vector3 newScale = Vector3.Lerp(startingScale, targetScale, interpolant);

            transform.localScale = newScale;

            // Play Trapped

            garden.TriggerTrapped(trappedSection);

            //optimization
            if (interpolant > 1)
            {
                isScaling = false;
                garden.StopTrapped(trappedSection);
            }
        }
    }


}