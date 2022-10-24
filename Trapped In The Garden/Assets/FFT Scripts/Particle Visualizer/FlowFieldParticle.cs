using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlowFieldParticle : MonoBehaviour
{
    int color; 
    public float _moveSpeed;
    public int _audioBand; 
    void Start()
    {
        
    }
    void Update()
    {
        this.transform.position += transform.forward * _moveSpeed * Time.deltaTime; 
        transform.GetChild(0).gameObject.GetComponent<ParticleSystemLayer1>().SetColor(color);

    }
    public void ApplyRotation(Vector3 rotation, float rotateSpeed)
    {
        Quaternion targetRotation = Quaternion.LookRotation(rotation.normalized);
        transform.rotation = Quaternion.RotateTowards(transform.rotation,targetRotation,rotateSpeed*Time.deltaTime);
    }
    public Vector3 getPosition()
    {
        return gameObject.transform.position; 
    }
    public int SetColor(int col)
    {
       return color = col; 
    }


}
