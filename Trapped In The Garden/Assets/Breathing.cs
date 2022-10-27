using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Breathing : MonoBehaviour
{
   	float rate = 0.2f;
    // Update is called once per frame
    void Update()
    {
    	float breathing = Mathf.Sin(Time.time) * rate;
    	transform.localScale += new Vector3(breathing, breathing, breathing) * Time.deltaTime;
        
    }
}
