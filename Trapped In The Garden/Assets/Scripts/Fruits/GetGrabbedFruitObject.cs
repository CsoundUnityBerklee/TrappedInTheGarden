using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Interaction.Toolkit;

public class GetGrabbedFruitObject : MonoBehaviour
{
    private XRRayInteractor interactor;
    private CsoundTransformAndPhysicsSender csoundTransformSender;
    private CsoundUnity csoundUnity;

    private bool canUpdateRotation = true;
    private bool rotationToggle = true;

    //Visual Feedback
    private Material fruitMaterial;
    private Renderer fruitRenderer;
    private Color fruitColor;
    private FruitVisualEffects fruitVfx;

    // Start is called before the first frame update
    void Awake()
    {
        interactor = GetComponent<XRRayInteractor>();
    }

    private void LateUpdate()
    {
        if (!rotationToggle)
        {
            fruitVfx.TieToRotation();
        }
    }

    public void GetGrabbedFruitCsound()
    {
        csoundTransformSender = interactor.selectTarget.GetComponentInChildren<CsoundTransformAndPhysicsSender>();
        csoundUnity = interactor.selectTarget.GetComponentInChildren<CsoundUnity>();
        fruitRenderer = interactor.selectTarget.GetComponent<Renderer>();
        fruitMaterial = fruitRenderer.material;
        fruitColor = fruitMaterial.color;
        fruitVfx = interactor.selectTarget.GetComponent<FruitVisualEffects>();
    }

    public void ResetReferences()
    {
        csoundTransformSender = null;
        csoundUnity = null;
        fruitRenderer = null;
        fruitMaterial = null;
    }

    public void UpdateCsoundPosition(bool update)
    {
        if (csoundTransformSender == null) { return; }

        if (!update)
        {
            csoundTransformSender.UpdatePosition(false);
        }
        else if(update)
        {
            csoundTransformSender.UpdatePosition(true);
        }
    }

    public void VolumeGateOn()
    {
        StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 0.1f, 0, 0));
        StartCoroutine(FadeAlpha(0.1f, 0, 0.25f));
        fruitVfx.StopParticleLoop();
    }

    public void VolumeGateOff()
    {
        StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 0.5f, 0, 1));
        StartCoroutine(FadeAlpha(0.5f, 0, 1));

        if (!rotationToggle)
        {
            fruitVfx.PlayParticleLoop();
        }
    }

    public void ToggleRotation()
    {
        if (rotationToggle)
        {
            csoundTransformSender.UpdateRotation(true);
            csoundUnity.SetChannel("reTrigger", 1);
            StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 0.05f, 0, 0.13f));
            fruitVfx.PlayParticleLoop();
            rotationToggle = false;
        }
        else
        {
            csoundUnity.SetChannel("reTrigger", 0);
            StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 3, 3.5f, 1f));
            csoundTransformSender.UpdateRotation(false);
            fruitVfx.StopParticleLoop();
            rotationToggle = true;
        }
    }

    private IEnumerator FadeAlpha(float duration, float delay, float targetValue)
    {
        yield return new WaitForSeconds(delay);
        float initialValue = fruitColor.a;
        float currentTime = 0;

        while (currentTime < duration)
        {
            currentTime += Time.deltaTime;
            fruitColor.a = Mathf.Lerp(initialValue, targetValue, currentTime / duration);
            fruitRenderer.material.color = fruitColor;
            yield return null;
        }
        yield break;
    }
}
