using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class DebugCollision : MonoBehaviour
{
    private TextMeshProUGUI text;

    // Start is called before the first frame update
    void Start()
    {
        text = GetComponent<TextMeshProUGUI>();
    }

    // Update is called once per frame
    public void DebugCollisionForce(float normalizedVector)
    {
        text.text = "COLLISION FORCE: " + normalizedVector;
    }
}
