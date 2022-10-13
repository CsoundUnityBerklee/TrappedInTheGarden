using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ReloadScene : MonoBehaviour
{
    public GetControllerButtonValues leftController, rightController;
    private int sceneIndex = 0;

    // Update is called once per frame
    void Update()
    {
        if(leftController.secondaryButtonValue == true && rightController.secondaryButtonValue == true)
        {
            LoadNextScene();
        }
    }

    private void ReloadCurrentScene()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void LoadNextScene()
    {
        sceneIndex++;
        if(sceneIndex > 2)
        {
            sceneIndex = 0;
        }
        SceneManager.LoadScene(sceneIndex);
    }
}
