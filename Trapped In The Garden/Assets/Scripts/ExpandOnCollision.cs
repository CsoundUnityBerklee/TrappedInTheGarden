using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExpandOnCollision : MonoBehaviour
{

    public bool Expand = false;

   void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Garden>())
        {
            
            Expand = true;
            //Destroy(this.gameObject.GetComponent<Rigidbody>());
            Destroy(this.gameObject, 15f);
            gameObject.GetComponent<Collider>().isTrigger = true;
        }

    }

    private void Update()
    {
        if (Expand)
        {
            transform.localScale += new Vector3(100, 100, 100 * Time.deltaTime);
        }
    }
}
