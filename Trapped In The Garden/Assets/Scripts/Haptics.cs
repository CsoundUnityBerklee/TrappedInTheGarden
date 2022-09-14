using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Interaction.Toolkit;


//TODO: Make Scriptable Objects as presets for haptics | Document code | Test with Quest





public enum HapticsControllers
{
    RightController,
    LeftController,
    Both
}

public class Haptics : MonoBehaviour
{
    [SerializeField] XRBaseController rightController, leftController;
    public HapticsControllers hController;


    [SerializeField] AnimationCurve _amplitude;
    float amplitudeValue;

    [Range(0.1f, 10f)]
    [SerializeField] float _duration;

    [Range(0.1f, 10f)]
    [SerializeField] float completeCycle;

    [SerializeField] bool debugHaptics = false;


    [ContextMenu("Send Haptics")]
    public void SendHaptics()
    {
        switch (hController)
        {
            case HapticsControllers.RightController:
                StartCoroutine(HapticEvent(rightController, null));
                break;
            case HapticsControllers.LeftController:
                StartCoroutine(HapticEvent(null, leftController));
                break;

            default:
                StartCoroutine(HapticEvent(rightController, leftController));
                break;
        }
    }


    IEnumerator HapticEvent(XRBaseController right, XRBaseController left)
    {
            float a = 0;


            while (a <= _duration){

            a += Time.deltaTime;
            amplitudeValue = _amplitude.Evaluate(Map(a, 0f, _duration, 0, 1));

            completeCycle = Mathf.Lerp(_duration, 0f, a / _duration);

            if (debugHaptics)
            {
                Debug.Log("Amplitude: " + amplitudeValue + " Time to Finish Cycle: " + completeCycle);
            }
           

            yield return 0;
        }
    }

    // Map Function
    float Map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}
