using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class DebugRotation : MonoBehaviour
{
    private TextMeshProUGUI text;
    public CsoundTransformAndPhysicsSender csoundObject;


    // Start is called before the first frame update
    void Start()
    {
        text = GetComponent<TextMeshProUGUI>();
    }

    // Update is called once per frame
    void Update()
    {
        string rotationDebug = "Rotation: " + csoundObject.gameObject.transform.rotation.eulerAngles;
        string rotationValueDebug = "Z Axis Rotation Value: " + csoundObject.RotationSender.zAxisValue;
        string positionDebug = "Relative Position: " + csoundObject.PositionSender.relativeCameraPos;

        text.text = rotationDebug + "\n" + rotationValueDebug + "\n" + positionDebug;

    }
}
