using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;

// TODO: Remove for URP 13.
// https://docs.unity3d.com/Packages/com.unity.render-pipelines.universal@13.1/manual/upgrade-guide-2022-1.html
#pragma warning disable CS0618

namespace FlatKit {
public class FlatKitOutline : ScriptableRendererFeature {
    [Tooltip("To create new settings use 'Create > FlatKit > Outline Settings'.")]
    public OutlineSettings settings;

    [SerializeField, HideInInspector]
    private Material _effectMaterial;

    private BlitTexturePass _blitTexturePass;

    private static readonly string OutlineShaderName = "Hidden/FlatKit/OutlineFilter";
    private static readonly int EdgeColor = Shader.PropertyToID("_EdgeColor");
    private static readonly int Thickness = Shader.PropertyToID("_Thickness");
    private static readonly int DepthThresholdMin = Shader.PropertyToID("_DepthThresholdMin");
    private static readonly int DepthThresholdMax = Shader.PropertyToID("_DepthThresholdMax");
    private static readonly int NormalThresholdMin = Shader.PropertyToID("_NormalThresholdMin");
    private static readonly int NormalThresholdMax = Shader.PropertyToID("_NormalThresholdMax");
    private static readonly int ColorThresholdMin = Shader.PropertyToID("_ColorThresholdMin");
    private static readonly int ColorThresholdMax = Shader.PropertyToID("_ColorThresholdMax");

    public override void Create() {
        if (settings == null) {
            Debug.LogWarning("[FlatKit] Missing Outline Settings");
            return;
        }

        _blitTexturePass ??= new BlitTexturePass() {
            renderPassEvent = settings.renderEvent
        };
    }

    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData) {
// #if UNITY_EDITOR
//         if (renderingData.cameraData.isPreviewCamera) {
//             return;
//         }
// #endif

        if (settings == null) {
            Debug.LogWarning("[FlatKit] Missing Outline Settings");
            return;
        }

        if (!CreateMaterials()) return;
        SetMaterialProperties();

        _blitTexturePass.Setup(_effectMaterial, settings.useDepth, settings.useNormals, useColor: true);
        renderer.EnqueuePass(_blitTexturePass);
    }

#if UNITY_2020_3_OR_NEWER
    protected override void Dispose(bool disposing) {
        CoreUtils.Destroy(_effectMaterial);
    }
#endif

    private bool CreateMaterials() {
        if (_effectMaterial == null) {
            var effectShader = Shader.Find(OutlineShaderName);
            var blitShader = Shader.Find(BlitTexturePass.CopyEffectShaderName);
            // Prevents Unity error on first import.
            if (effectShader == null || blitShader == null) return false;
            _effectMaterial = CoreUtils.CreateEngineMaterial(effectShader);
        }

        Debug.Assert(_effectMaterial != null, $"[Flat Kit] Missing Material {OutlineShaderName}");

        return true;
    }

    private void SetMaterialProperties() {
        if (_effectMaterial == null) {
            return;
        }

        const string depthKeyword = "OUTLINE_USE_DEPTH";
        if (settings.useDepth) {
            _effectMaterial.EnableKeyword(depthKeyword);
        } else {
            _effectMaterial.DisableKeyword(depthKeyword);
        }

        const string normalsKeyword = "OUTLINE_USE_NORMALS";
        if (settings.useNormals) {
            _effectMaterial.EnableKeyword(normalsKeyword);
        } else {
            _effectMaterial.DisableKeyword(normalsKeyword);
        }

        const string colorKeyword = "OUTLINE_USE_COLOR";
        if (settings.useColor) {
            _effectMaterial.EnableKeyword(colorKeyword);
        } else {
            _effectMaterial.DisableKeyword(colorKeyword);
        }

        const string outlineOnlyKeyword = "OUTLINE_ONLY";
        if (settings.outlineOnly) {
            _effectMaterial.EnableKeyword(outlineOnlyKeyword);
        } else {
            _effectMaterial.DisableKeyword(outlineOnlyKeyword);
        }

        const string resolutionInvariantKeyword = "RESOLUTION_INVARIANT_THICKNESS";
        if (settings.resolutionInvariant) {
            _effectMaterial.EnableKeyword(resolutionInvariantKeyword);
        } else {
            _effectMaterial.DisableKeyword(resolutionInvariantKeyword);
        }

        _effectMaterial.SetColor(EdgeColor, settings.edgeColor);
        _effectMaterial.SetFloat(Thickness, settings.thickness);

        _effectMaterial.SetFloat(DepthThresholdMin, settings.minDepthThreshold);
        _effectMaterial.SetFloat(DepthThresholdMax, settings.maxDepthThreshold);

        _effectMaterial.SetFloat(NormalThresholdMin, settings.minNormalsThreshold);
        _effectMaterial.SetFloat(NormalThresholdMax, settings.maxNormalsThreshold);

        _effectMaterial.SetFloat(ColorThresholdMin, settings.minColorThreshold);
        _effectMaterial.SetFloat(ColorThresholdMax, settings.maxColorThreshold);
    }
}
}