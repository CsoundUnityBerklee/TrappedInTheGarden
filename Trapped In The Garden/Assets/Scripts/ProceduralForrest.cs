using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProceduralForrest : MonoBehaviour
{
    [SerializeField] GameObject[] _models;
    [SerializeField] int numberOfObjects;

    // Start is called before the first frame update
    void Start()
    {
        GenerateForrest();
    }

    void GenerateForrest()
    {
        for (int i = 0; i < numberOfObjects; i++)
        {
            float posX = Random.Range(-80, 80);
            float posZ = Random.Range(-80, 80);

            Vector3 randomPos = new Vector3(posX, this.transform.position.y - 0.5f, posZ);
            GameObject newSample = Instantiate(_models[Random.Range(0, _models.Length)], randomPos, this.transform.rotation);

        }
    }
}
