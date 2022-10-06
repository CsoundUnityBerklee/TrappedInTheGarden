using UnityEngine;
using UnityEngine.Rendering.Universal;

namespace FlatKit {
[CreateAssetMenu(fileName = "FogSettings", menuName = "FlatKit/Fog Settings")]
public class FogSettings : ScriptableObject {
    [Header("Distance Fog")]
    public bool useDistance = true;

    public Gradient distanceGradient;
    public float near = 0;
    public float far = 100;

    [Range(0, 1)]
    public float distanceFogIntensity = 1.0f;

    public bool useDistanceFogOnSky = false;

    [Header("Height Fog")]
    [Space]
    public bool useHeight = false;

    public Gradient heightGradient;
    public float low = 0;
    public float high = 10;

    [Range(0, 1)]
    public float heightFogIntensity = 1.0f;

    public bool useHeightFogOnSky = false;

    [Header("Blending")]
    [Space]
    [Range(0, 1)]
    public float distanceHeightBlend = 0.5f;

    [Header("Advanced settings")]
    [Space, Tooltip(
         "The render stage at which the effect is applied. To exclude transparent objects, like water or UI elements, " +
         "set this to \"Before Transparent\".")]
    public RenderPassEvent renderEvent = RenderPassEvent.BeforeRenderingPostProcessing;

    private void OnValidate() {
        if (low > high) {
            Debug.LogWarning(
                "[FlatKit] Fog Height configuration error: 'Low' must not be greater than 'High'");
        }

        if (near > far) {
            Debug.LogWarning(
                "[FlatKit] Fog Distance configuration error: 'Near' must not be greater than 'Far'");
        }
    }
}
}