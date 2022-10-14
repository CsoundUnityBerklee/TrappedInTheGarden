using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.Interaction.Toolkit;

public class GetGrabbedFruitObject : MonoBehaviour
{
    private XRDirectInteractor interactor;
    private CsoundTransformAndPhysicsSender csoundTransformSender;
    private CsoundSender csoundSender;
    private CsoundUnity csoundUnity;

    private bool canUpdateRotation = true;
    private bool rotationToggle = true;

    // Start is called before the first frame update
    void Awake()
    {
        interactor = GetComponent<XRDirectInteractor>();
    }

    public void GetGrabbedFruitCsound()
    {
        csoundTransformSender = interactor.selectTarget.GetComponentInChildren<CsoundTransformAndPhysicsSender>();
        csoundSender = interactor.selectTarget.GetComponentInChildren<CsoundSender>();
        csoundUnity = interactor.selectTarget.GetComponentInChildren<CsoundUnity>();
    }

    public void ResetReferences()
    {
        csoundTransformSender = null;
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
        csoundUnity.SetChannel("masterLvl", 0);
    }

    public void VolumeGateOff()
    {
        csoundUnity.SetChannel("masterLvl", 1);
    }

    public void ToggleRotation()
    {
        if (rotationToggle)
        {
            csoundTransformSender.UpdateRotation(true);
            csoundUnity.SetChannel("reTrigger", 1);
            csoundUnity.SetChannel("masterLvl", 0.25f);
            rotationToggle = false;
        }
        else
        {
            csoundUnity.SetChannel("reTrigger", 0);
            csoundUnity.SetChannel("masterLvl", 1f);
            csoundTransformSender.UpdateRotation(false);
            rotationToggle = true;
        }
    }
}
