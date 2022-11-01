using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class CsoundTriggerDelayed : MonoBehaviour
{
    private CsoundSender csoundSender;
    public AudioMixer mixer;
    private string masterVolumeParameter = "MasterVolume";

    // Start is called before the first frame update
    void Awake()
    {
        csoundSender = GetComponent<CsoundSender>();
        StartCoroutine(FadeInMaster());
    }

    private void Start()
    {
        StartCoroutine(DelayedTrigger());
    }

    private IEnumerator FadeInMaster()
    {
        StartCoroutine(AudioUtility.FadeMixerGroup(mixer, masterVolumeParameter, 0.01f, 0));
        yield return new WaitForSeconds(15f);
        StartCoroutine(AudioUtility.FadeMixerGroup(mixer, masterVolumeParameter, 6f, 1));
    }

    private IEnumerator DelayedTrigger()
    {
        yield return new WaitForSeconds(15f);
        csoundSender.ToggleTrigger();
    }
}
