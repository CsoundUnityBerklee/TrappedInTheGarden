using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class CombineControllerInputs : MonoBehaviour
{
    public GetControllerButtonValues inputLeft, inputRight;
    public AudioMixer mixer;
    private string masterVolumeParameter = "MasterVolume";
    private float fadeInDuration = 2.5f, fadeOutDuration = 5f;
    private bool canFadeOut = true;

    // Update is called once per frame
    void Update()
    {
        CheckInputs();
    }

    private void CheckInputs()
    {
        if(inputLeft.primaryButtonValue && inputLeft.secondaryButtonValue && inputRight.primaryButtonValue && inputRight.secondaryButtonValue)
        {
            FadeOutMaster();
        }

        if(inputLeft.gripButtonValue && inputLeft.triggerButtonValue && inputRight.gripButtonValue && inputLeft.triggerButtonValue)
        {
            FadeInMaster();
        }
    }

    public void FadeInMaster()
    {
        if (!canFadeOut)
        {
            StartCoroutine(AudioUtility.FadeMixerGroup(mixer, masterVolumeParameter, fadeInDuration, 1));
            canFadeOut = true;
        }
    }

    public void FadeOutMaster()
    {
        if (canFadeOut)
        {
            StartCoroutine(AudioUtility.FadeMixerGroup(mixer, masterVolumeParameter, fadeOutDuration, 0));
            canFadeOut = false;
        }
    }
}
