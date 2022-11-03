using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExpandOnCollision : MonoBehaviour
{

    float x, y, z;
    public bool Expand = false;


    void Start(){
        x = Random.Range(10f, 120f);
        y = Random.Range(10f, 120f);
        z = Random.Range(10f, 120f);

    }

   void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            
            Expand = true;
            //Destroy(this.gameObject.GetComponent<Rigidbody>());
            Destroy(this.gameObject, 12f);
            gameObject.GetComponent<Collider>().isTrigger = true;
        }

    }

    private void Update()
    {
        if (Expand)
        {
            transform.localScale += new Vector3(x, y, z * Time.deltaTime);
        }
    }
}
