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

    // Start is called before the first frame update
    void Awake()
    {
        interactor = GetComponent<XRRayInteractor>();
    }

    //public void GetGrabbedFruitCsound()
    //{
    //    csoundTransformSender = interactor.selectTarget.GetComponentInChildren<CsoundTransformAndPhysicsSender>();
    //    csoundUnity = interactor.selectTarget.GetComponentInChildren<CsoundUnity>();
    //}

    public void ResetReferences()
    {
        csoundTransformSender = null;
        csoundUnity = null;
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
    }

    public void VolumeGateOff()
    {
        StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 0.5f, 0, 1));
    }

    public void ToggleRotation()
    {
        if (rotationToggle)
        {
            csoundTransformSender.UpdateRotation(true);
            csoundUnity.SetChannel("reTrigger", 1);
            StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 0.05f, 0, 0.15f));
            rotationToggle = false;
        }
        else
        {
            csoundUnity.SetChannel("reTrigger", 0);
            StartCoroutine(InterpolateCsoundChannelValue.LerpChannelValue(csoundUnity, "masterLvl", 3, 2f, 1f));
            csoundTransformSender.UpdateRotation(false);
            rotationToggle = true;
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.CompareTag("Fruit"))
        {
            csoundTransformSender = collision.gameObject.GetComponentInChildren<CsoundTransformAndPhysicsSender>();
            csoundUnity = collision.gameObject.GetComponentInChildren<CsoundUnity>();
        }
    }
}
