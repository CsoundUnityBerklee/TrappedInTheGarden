using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HandAnimation : MonoBehaviour
{
    public GetControllerButtonValues buttonValues;
    private Animator animator;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        UpdateHandAnimation();
    }

    void UpdateHandAnimation()
    {
        animator.SetFloat("Trigger", buttonValues.triggerValue);
        animator.SetFloat("Grip", buttonValues.gripValue);
    }
}
