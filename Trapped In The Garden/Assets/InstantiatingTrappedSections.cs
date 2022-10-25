using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstantiatingTrappedSections : MonoBehaviour
{
    [SerializeField] GameObject[] _objects;
    //[SerializeField] int count = 0;
    [SerializeField] Transform positionOrigin;




    public void InstanceOfTrapped()
    {
        
        Instantiate(_objects[Random.Range(0, _objects.Length)], positionOrigin.position, Quaternion.identity);
        //count++;

        //if (count > _objects.Length)
        //{
        //    count = 0;
        //}
    }
}
