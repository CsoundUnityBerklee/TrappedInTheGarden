using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TreeGenerator : MonoBehaviour
{
    public GameObject fruitPrefab;
    public CsoundUnityPreset[] presets;

    private List<GameObject> fruitPositions = new List<GameObject>();
    private List<GameObject> spawnedFruits = new List<GameObject>();
    
    // Start is called before the first frame update
    void Awake()
    {
        GetAllFruitPositionChildren();
    }

    void Start()
    {
        InstantiateFruitsAndAssignPresets();
    }

    private void GetAllFruitPositionChildren()
    {
        int childCount = transform.childCount;

        for(int i = 0; i < childCount; i++)
        {
            GameObject childObject = transform.GetChild(i).gameObject;

            if (childObject.CompareTag("FruitPosition"))
            {
                fruitPositions.Add(childObject);
            }
        }
    }

    private void InstantiateFruitsAndAssignPresets()
    {
        //Intantiate fruits
        foreach (GameObject fruitPosition in fruitPositions)
        {
            GameObject spawnedFruit = Instantiate(fruitPrefab, fruitPosition.transform.position, fruitPosition.transform.rotation);
            spawnedFruit.transform.parent = gameObject.transform;
            spawnedFruits.Add(spawnedFruit);
        }

        //Assigns presets
        for(int i = 0;  i < spawnedFruits.Count; i++)
        {
            CsoundUnity csound = spawnedFruits[i].GetComponentInChildren<CsoundUnity>();
            csound.SetPreset(presets[i]);
        }
    }
}
