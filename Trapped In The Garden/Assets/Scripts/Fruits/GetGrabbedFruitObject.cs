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
    private bool toggleRotation = true;

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

    public void ToggleCsoundRotation()
    {
        if (csoundTransformSender == null) { return; }

        if (toggleRotation)
        {
            csoundUnity.SetChannel("reTrigger", 1);
            csoundTransformSender.UpdateRotation(toggleRotation);
            toggleRotation = false;
        }
        else
        {
            csoundUnity.SetChannel("reTrigger", 0);
            csoundTransformSender.UpdateRotation(toggleRotation);
            toggleRotation = true;
        }
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

    public void HoldUpdateCsoundRotation(bool update)
    {
        if (csoundTransformSender == null) { return; }

        if (!update && canUpdateRotation == false)
        {
            csoundUnity.SetChannel("reTrigger", 0);
            csoundTransformSender.UpdateRotation(false);
            canUpdateRotation = true;
        }
        else if(canUpdateRotation == true)
        {
            csoundTransformSender.UpdateRotation(true);
            csoundUnity.SetChannel("reTrigger", 1);
            canUpdateRotation = false;
        }
    }
}
