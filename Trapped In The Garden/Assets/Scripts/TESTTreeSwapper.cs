using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TESTTreeSwapper : MonoBehaviour
{
    public GameObject[] trees;
    int index = 0;

    //private void Start()
    //{
    //    StartCoroutine(Test());
    //}

    private IEnumerator Test()
    {
        yield return new WaitForSeconds(1.2f);
        PreviousTree();
        StartCoroutine(Test());
    }

    public void NextTree()
    {
        trees[index].SetActive(false);
        index++;

        if(index >= trees.Length)
        {
            index = 0;
        }

        trees[index].SetActive(true);
    }

    public void PreviousTree()
    {
        trees[index].SetActive(false);
        index--;

        if (index < 0)
        {
            index = trees.Length - 1;
        }

        trees[index].SetActive(true);
    }
}
