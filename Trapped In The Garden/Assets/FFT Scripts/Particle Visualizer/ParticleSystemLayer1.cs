using System.CodeDom.Compiler;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleSystemLayer1 : MonoBehaviour
{
    bool colorChangeTriggered = false;
    int currentColor;
    
    AudioFlowfield audio; 

    // 0 : sad, blue
    // 1 : neutral : white, grey
    // 2 : happy : red

    ParticleSystem particleGlow;

    //RGB Values
    float red =0;
    float green =0;
    float blue =0;

    [SerializeField]

    void Start()
    {
        particleGlow = gameObject.GetComponent<ParticleSystem>();
        var main = particleGlow.main;
        main.startColor = new Color(0, 0, 0, 0);
    }

    
    void Update()
    {
        var main = particleGlow.main;
        if (colorChangeTriggered)
        {
            //var main = particleGlow.main;

            switch (currentColor)
            {
                case 0:
                    //GenerateRGB(0);
                    main.startColor = new Color(0.1f, 0.2f, 0.8f, 1);
                    break;
                case 1:
                    //GenerateRGB(1);
                    main.startColor = new Color(1, 0.92f, 0.8f, 1);
                    break;
                case 2:
                    //GenerateRGB(2);
                    main.startColor = new Color(0.8f, 0.2f, 0.1f, 1);
                    break;
                default:
                    main.startColor = new Color(0, 0, 0, 0);
                    Debug.Log("Wrong input");
                    break;
            }
            colorChangeTriggered = false;
        }
        //main.startSize = audio.scale; 
            
    }

    public void SetColor(int Incomingcolor)
    {
        if (currentColor != Incomingcolor)
        {
            currentColor = Incomingcolor;
            colorChangeTriggered = true;
        }
        
    }
    void GenerateRGB(int local)
    {
        switch (local)
        {
            case 0:
                red = Random.Range(0,50);
                green = Random.Range(0,50);
                blue = Random.Range(200, 255);
                break;
            case 1:
                red = 205;
                green = 199;
                blue = 34;
                break;
            case 2:
                red = Random.Range(200, 255);
                green = Random.Range(0, 50);
                blue = Random.Range(0,50);
                break;
            default:
                red = 0;
                green = 0;
                blue = 0;
                break;

        }
    }

    
}