using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Interaction.Toolkit;

public class InteractionSwapper : MonoBehaviour
{
    public GetControllerButtonValues leftControllerValues, rightControllerValues;

    [Header("HANDS AND DIRECT INTERACTOR")]
    public GameObject handModel;
    private XRDirectInteractor directInteractor;
    [Header("RAY INTERACTOR")]
    public GameObject handObject;
    private 

    // Start is called before the first frame update
    void Awake()
    {
        directInteractor = GetComponent<XRDirectInteractor>();

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
