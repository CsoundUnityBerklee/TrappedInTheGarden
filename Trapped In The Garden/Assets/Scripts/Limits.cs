using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Limits : MonoBehaviour
{
    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.GetComponent<InstantiatingTrappedSections>())
        {
            Destroy(this.gameObject);
        }
    }
}
