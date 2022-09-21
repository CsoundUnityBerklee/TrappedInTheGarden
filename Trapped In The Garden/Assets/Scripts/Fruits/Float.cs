using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Float : MonoBehaviour
{
    public float strengthY = 0.2f;
    public float strengthX = 0.1f;

    // Update is called once per frame
    void Update()
    {
        FloatingTransform();
    }

    private void FloatingTransform()
    {
        float floatY = Mathf.Sin(Time.time) * strengthY;
        float floatX = Mathf.Sin(Time.time) * strengthX;

        Vector3 floatingVector = new Vector3(floatX, floatY, 0);
        transform.position = transform.position + floatingVector;
    }

}
