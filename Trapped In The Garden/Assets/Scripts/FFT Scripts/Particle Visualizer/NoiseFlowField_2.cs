using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.TextCore.LowLevel;
using UnityEngine.UIElements;

public class NoiseFlowField_2 : MonoBehaviour
{

    FastNoise _fastNoise;
    [SerializeField] Vector3Int _gridSize;
    [SerializeField] float _cellSize; 
    [SerializeField] float _increment;
    [SerializeField] Vector3 _offset, _offsetSpeed;
    [SerializeField] Vector3[,,] flowfieldDirectionStorage;

    // Particle Attributes

    [SerializeField] GameObject _particlePrefab;
    public int _amountOfParticles;// TOTAL NUMBER OF PARTICLES IN ENCLOSURE
    public List<GameObject> _particles; //EACH ELEMENT IN THIS LIST IS A PARTICLE
    public List<FlowFieldParticle> _particleList;
    [SerializeField] float _particleScale;//SIZE OF PARTICLE
    [SerializeField] float _spawnRadius;// MIN DISTANCE EACH PARTICLE HAS TO BE APART FROM EACH OTHER
    int attempt = 0;
    int countParticles = 0; 
    bool flag = false; 
   
    // Particle movement Attributes

    public float _particleMoveSpeed, _particleRotateSpeed; 

    //Particle Color
    [SerializeField] int color = 0;
    public List<MeshRenderer> _particleMeshRenderer; 


    void Awake()
    {
        flowfieldDirectionStorage = new Vector3[_gridSize.x, _gridSize.y, _gridSize.z];
        _fastNoise = new FastNoise();
        _particles = new List<GameObject>();
        _particleList = new List<FlowFieldParticle>();
        _particleMeshRenderer = new List<MeshRenderer>();
        SpawnParticles();
        
    }        
    void Update()
    {
        CalulateFlowFieldDirections();
        ParticleBehavior();
    }
    void SpawnParticles()
    {
        for (int i = 0; i < _amountOfParticles; i++)
        {
            while (attempt < 100)
            {
                //GENERATE A RANDOM POSITION IN ENCLOSURE
                Vector3 randomPos = new Vector3(
                               Random.Range(this.transform.position.x, this.transform.position.x + _gridSize.x * _cellSize),
                               Random.Range(this.transform.position.y, this.transform.position.y + _gridSize.y * _cellSize),
                               Random.Range(this.transform.position.z, this.transform.position.z + _gridSize.z * _cellSize)
                               );
                //CHECK IF THE SPOT GENERATED IS OCCUPIED
                if (SpotNotOccupied(randomPos))
                {
                    GameObject particleInstance = Instantiate(_particlePrefab, randomPos, _particlePrefab.transform.rotation, this.transform);
                    particleInstance.transform.localScale = new Vector3(_particleScale, _particleScale, _particleScale);
                    _particles.Add(particleInstance);
                    _particleList.Add(particleInstance.GetComponent<FlowFieldParticle>());
                    _particleMeshRenderer.Add(particleInstance.GetComponent<MeshRenderer>());
                    countParticles++; 
                    break;
                }
                //IF IT IS, REATTEMPT GENERATION OF RANDOM POINT 
                else
                {
                    attempt++;
                }
            }
        }
    }
    void CalulateFlowFieldDirections()
    {
        MakeDynammicFlowField();
        float xOff = 0f;
        for (int x = 0; x < _gridSize.x; x++)
        {
            float yOff = 0f;
            for (int y = 0; y < _gridSize.y; y++)
            {
                float zOff = 0f;

                for (int z = 0; z < _gridSize.z; z++)
                {
                    float noise = _fastNoise.GetSimplex(xOff + _offset.x, yOff + _offset.y, zOff + _offset.z) + 1;

                    Vector3 noiseDirection = new Vector3(Mathf.Cos(noise * Mathf.PI), Mathf.Sin(noise * Mathf.PI), Mathf.Cos(noise * Mathf.PI));// returns a direction for each cube
                    flowfieldDirectionStorage[x, y, z] = Vector3.Normalize(noiseDirection);
                    //storing noise direction
                    zOff += _increment;
                }
                yOff += _increment;
            }
            xOff += _increment;
        }

    }
    void MakeDynammicFlowField()
    {
        _offset = new Vector3(_offset.x + (_offsetSpeed.x * Time.deltaTime), _offsetSpeed.y + (_offsetSpeed.y * Time.deltaTime), _offsetSpeed.z + (_offsetSpeed.z * Time.deltaTime));
    }
    bool SpotNotOccupied(Vector3 position1)
    {
        foreach (GameObject p in _particles)
        {
            if (p == null)
            {
                return true;
            }


            if (Vector3.Distance(position1, p.transform.position) < _spawnRadius)
            {
                Debug.Log("Right");
                return false;
            }

        }
        return true;
    }
    void ParticleBehavior()
    {
        foreach (FlowFieldParticle p in _particleList)
        {
            KeepInBound(p);
            Vector3Int particlePos = new Vector3Int(
            Mathf.FloorToInt(Mathf.Clamp(p.getPosition().x - this.transform.position.x / _cellSize, 0, _gridSize.x - 1)),
            Mathf.FloorToInt(Mathf.Clamp(p.getPosition().y - this.transform.position.y / _cellSize, 0, _gridSize.y - 1)),
            Mathf.FloorToInt(Mathf.Clamp(p.getPosition().z - this.transform.position.z / _cellSize, 0, _gridSize.z - 1))
            );
            p.ApplyRotation(flowfieldDirectionStorage[particlePos.x, particlePos.y, particlePos.z], _particleRotateSpeed);
            p._moveSpeed = _particleMoveSpeed;
            p.transform.localScale = new Vector3(_particleScale, _particleScale, _particleScale);    
            p.SetColor(color);       
        }
    }
    private void OnDrawGizmos()
    {
        Gizmos.color = Color.white;
        //param: center & size of cube
        Gizmos.DrawWireCube(this.transform.position + new Vector3((_gridSize.x*_cellSize)*0.5f, (_gridSize.y * _cellSize) * 0.5f, (_gridSize.z * _cellSize) * 0.5f),
        new Vector3(_gridSize.x*_cellSize,_gridSize.y*_cellSize, _gridSize.z * _cellSize));
    }
    void KeepInBound(FlowFieldParticle p)
    {
        //X BOUND
        if(p.getPosition().x > this.transform.position.x + (_gridSize.x * _cellSize))
        {
            p.transform.position = new Vector3(this.transform.position.x, p.transform.position.y, p.transform.position.z);
        }
        if (p.getPosition().x < this.transform.position.x)
        {
            p.transform.position = new Vector3(this.transform.position.x + (_gridSize.x * _cellSize), p.transform.position.y, p.transform.position.z);
        }

        //Y BOUND
        if (p.getPosition().y > this.transform.position.y + (_gridSize.y * _cellSize))
        {
            p.transform.position = new Vector3(p.transform.position.x, this.transform.position.y, p.transform.position.z);
        }
        if (p.getPosition().y < this.transform.position.y)
        {
            p.transform.position = new Vector3(p.transform.position.x, this.transform.position.y + (_gridSize.y * _cellSize), p.transform.position.z);
        }

        //Z BOUND
        if (p.getPosition().z > this.transform.position.z + (_gridSize.x * _cellSize))
        {
            p.transform.position = new Vector3(p.transform.position.x, p.transform.position.y, this.transform.position.z);
        }
        if (p.getPosition().z < this.transform.position.z)
        {
            p.transform.position = new Vector3(p.transform.position.x, p.transform.position.y, this.transform.position.z + (_gridSize.z * _cellSize));
        }

    }
    public int getColor()
    {
        return color; 
    }

}