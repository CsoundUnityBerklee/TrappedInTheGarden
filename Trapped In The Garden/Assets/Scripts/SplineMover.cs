using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SplineMover : MonoBehaviour
{

    public Spline spline;

    public float lerpDampening = 10f;
    
    Transform followObj; //What we follow

    private Transform thisTransform;
    // Start is called before the first frame update
    void Start()
    {
        thisTransform = transform;
        followObj = Camera.main?.transform; //Will get the player
        if (followObj == null) Destroy(this);
    }

    // Update is called once per frame
    void Update()
    {
        thisTransform.position = Vector3.Lerp(thisTransform.position, spline.WhereOnSpline(followObj.position), lerpDampening * Time.deltaTime);
    }

}
