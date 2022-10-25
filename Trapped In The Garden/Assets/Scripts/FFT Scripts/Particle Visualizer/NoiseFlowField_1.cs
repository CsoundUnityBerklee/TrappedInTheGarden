using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEngine;

public class NoiseFlowField_1 : MonoBehaviour
{
    FastNoise _fastNoise;
    [SerializeField] Vector3Int _gridSize;
    [SerializeField] float _increment;
    [SerializeField] Vector3 _offset, _offsetSpeed; 
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnDrawGizmos()
    {
        _fastNoise = new FastNoise();
        float xOff = 0f;
        for(int x = 0; x<_gridSize.x; x++)
        {
            float yOff = 0f;
            for (int y = 0; y < _gridSize.x; y++)
            {
                float zOff = 0f;

                for (int z = 0; z < _gridSize.z; z++)
                {
                    float noise = _fastNoise.GetSimplex(xOff+_offset.x, yOff + _offset.y, zOff + _offset.z) + 1;

                    Vector3 noiseDirection = new Vector3(Mathf.Cos(noise*Mathf.PI), Mathf.Sin(noise * Mathf.PI), Mathf.Cos(noise * Mathf.PI));// returns a direction for each cube

                    //Gizmos.color = new Color(1, 1, 1, noise * 0.5f); //last param is opacity, returns a color for each cube

                    Gizmos.color = new Color(noiseDirection.normalized.x, noiseDirection.normalized.y, noiseDirection.normalized.z,1f);
                    Vector3 pos = new Vector3(x, y, z) + transform.position;

                    //Vector3 size = new Vector3(1, 1, 1);
                    //Drawing a line

                    Vector3 endPos = pos + Vector3.Normalize(noiseDirection);


                    //Gizmos.DrawCube(pos, size);

                    Gizmos.DrawLine(pos, endPos);
                    Gizmos.DrawSphere(endPos, 0.1f);
                    zOff += _increment; 
                }
                yOff += _increment; 
            }
            xOff += _increment;
        }
    }

   
    
}