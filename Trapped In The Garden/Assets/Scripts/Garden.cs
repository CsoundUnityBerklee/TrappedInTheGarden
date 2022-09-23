using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Garden : MonoBehaviour
{
    CsoundUnity csound;

    string sectionNameTrigger, sectionNameStop;

    public void Start()
    {
        csound = GetComponent<CsoundUnity>();
    }


    public void TriggerTrapped(int section)
    {

        // Determine which section will be rendered
        switch (section)
        {
            case 0:
                sectionNameTrigger = "trigSec1";
                break;
            case 1:
                sectionNameTrigger = "trigSec1a";
                break;
            case 2:
                sectionNameTrigger = "trigSec2";
                break;
            case 3:
                sectionNameTrigger = "trigSec2a";
                break;
            case 4:
                sectionNameTrigger = "trigSec3";
                break;
            case 5:
                sectionNameTrigger = "trigSec3a";
                break;
            case 7:
                sectionNameTrigger = "trigSec4";
                break;
            case 8:
                sectionNameTrigger = "trigSec4a";
                break;
            case 9:
                sectionNameTrigger = "trigSec4b";
                break;
            case 10:
                sectionNameTrigger = "trigSec4c";
                break;
        }

        csound.SetChannel(sectionNameTrigger, 1);
    }

    public void StopTrapped(int section)
    {
        // Determine which section will be rendered
        switch (section)
        {
            case 0:
                sectionNameStop = "stopgSec1";
                break;
            case 1:
                sectionNameStop = "stopSec1a";
                break;
            case 2:
                sectionNameStop = "stopSec2";
                break;
            case 3:
                sectionNameStop = "stopSec2a";
                break;
            case 4:
                sectionNameStop = "stopSec3";
                break;
            case 5:
                sectionNameStop = "stopSec3a";
                break;
            case 7:
                sectionNameStop = "stopSec4";
                break;
            case 8:
                sectionNameStop = "stopSec4a";
                break;
            case 9:
                sectionNameStop = "stopSec4b";
                break;
            case 10:
                sectionNameStop = "stopSec4c";
                break;
        }

        csound.SetChannel(sectionNameStop, 1);
    }

}

