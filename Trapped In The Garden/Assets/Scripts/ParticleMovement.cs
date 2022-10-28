using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleMovement : MonoBehaviour
{
    [Range(0.01f, 5f)] // just for this example
    public float _speed;

    float Xvec, Yvec, Zvec;  

    private void Start()
    {
        InvokeRepeating("UpdatePosition", 5f, 1f);
    }

    private void Update()
    {
        transform.position = new Vector3(transform.position.x + Xvec, transform.position.y + Yvec, transform.position.z + Zvec) * Time.deltaTime * _speed;
    }


    void UpdatePosition()
    {
        Xvec = Random.Range(-2, 3);
        Yvec = Random.Range(-2, 3);
        Zvec = Random.Range(-2, 3);


    }
}
