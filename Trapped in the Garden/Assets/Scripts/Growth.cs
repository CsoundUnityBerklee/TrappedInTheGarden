using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Growth : MonoBehaviour
{
    // Seconds
    [SerializeField] float scalingDuration = 5f;

    // Target Scale
    [SerializeField] Vector3 targetScale = Vector3.one * .1f;

    // Starting Scale
    Vector3 startingScale;

    // t for linear interpolation
    float interpolant = 0;


    [SerializeField] bool isScaling = false;


    void Start()
    {
        startingScale = this.transform.localScale;
        interpolant = 0;
    }

    void Update()
    {
        ScaleDown();
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

            //optimization
            if (interpolant > 1)
            {

                isScaling = false;

            }
        }

    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            isScaling = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            transform.localScale = startingScale;
        }
    }




}