using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;

// TODO: Remove for URP 13.
// https://docs.unity3d.com/Packages/com.unity.render-pipelines.universal@13.1/manual/upgrade-guide-2022-1.html
#pragma warning disable CS0618

namespace FlatKit {
internal class BlitTexturePass : ScriptableRenderPass {
    public static readonly string CopyEffectShaderName = "Hidden/FlatKit/CopyTexture";

    private ProfilingSampler _profilingSampler;
    private Material _effectMaterial;
    private Material _copyMaterial;
    private RenderTargetHandle _temporaryColorTexture;

    public void Setup(Material effectMaterial, bool useDepth, bool useNormals, bool useColor) {
        _effectMaterial = effectMaterial;
        var name = effectMaterial.name.Substring(effectMaterial.name.LastIndexOf('/') + 1);
        _profilingSampler = new ProfilingSampler($"Blit {name}");

        _copyMaterial = CoreUtils.CreateEngineMaterial(CopyEffectShaderName);
        
#if UNITY_2020_3_OR_NEWER
        ConfigureInput(
            (useColor ? ScriptableRenderPassInput.Color : ScriptableRenderPassInput.None) |
            (useDepth ? ScriptableRenderPassInput.Depth : ScriptableRenderPassInput.None) |
            (useNormals ? ScriptableRenderPassInput.Normal : ScriptableRenderPassInput.None)
        );
#endif
    }

    public override void OnCameraSetup(CommandBuffer cmd, ref RenderingData renderingData) {
        ConfigureTarget(new RenderTargetIdentifier(renderingData.cameraData.renderer.cameraColorTarget, 0,
            CubemapFace.Unknown, -1));
    }

    public override void Execute(ScriptableRenderContext context, ref RenderingData renderingData) {
        if (_effectMaterial == null) return;
        if (renderingData.cameraData.camera.cameraType != CameraType.Game) return;

        _temporaryColorTexture = new RenderTargetHandle();

        CommandBuffer cmd = CommandBufferPool.Get();
        using (new ProfilingScope(cmd, _profilingSampler)) {
            var descriptor = renderingData.cameraData.cameraTargetDescriptor;
            descriptor.depthBufferBits = 0;
            SetSourceSize(cmd, descriptor);

#if UNITY_2022_1_OR_NEWER
            var cameraTargetHandle = renderingData.cameraData.renderer.cameraColorTargetHandle;
#else
            var cameraTargetHandle = renderingData.cameraData.renderer.cameraColorTarget;
#endif
            cmd.GetTemporaryRT(_temporaryColorTexture.id, descriptor);

            // Also seen as `renderingData.cameraData.xr.enabled` and `#if ENABLE_VR && ENABLE_XR_MODULE`.
            if (renderingData.cameraData.xrRendering) {
                _effectMaterial.EnableKeyword("_USE_DRAW_PROCEDURAL"); // `UniversalRenderPipelineCore.cs`.
                cmd.SetRenderTarget(_temporaryColorTexture.Identifier());
                cmd.DrawMesh(RenderingUtils.fullscreenMesh, Matrix4x4.identity, _effectMaterial, 0, 0);
                cmd.SetGlobalTexture("_EffectTexture", _temporaryColorTexture.Identifier());
                cmd.SetRenderTarget(new RenderTargetIdentifier(cameraTargetHandle, 0, CubemapFace.Unknown, -1));
                cmd.DrawMesh(RenderingUtils.fullscreenMesh, Matrix4x4.identity, _copyMaterial, 0, 0);
            } else {
                _effectMaterial.DisableKeyword("_USE_DRAW_PROCEDURAL");
                // Note: `FinalBlitPass` has `cmd.SetRenderTarget` at this point, but it's unclear what that does.
                cmd.Blit(cameraTargetHandle, _temporaryColorTexture.Identifier(), _effectMaterial, 0);
                cmd.Blit(_temporaryColorTexture.Identifier(), cameraTargetHandle);
            }
        }

        context.ExecuteCommandBuffer(cmd);
        cmd.Clear();
        CommandBufferPool.Release(cmd);
    }

    // Copied from `PostProcessUtils.cs`.
    private static void SetSourceSize(CommandBuffer cmd, RenderTextureDescriptor desc) {
        float width = desc.width;
        float height = desc.height;
        if (desc.useDynamicScale) {
            width *= ScalableBufferManager.widthScaleFactor;
            height *= ScalableBufferManager.heightScaleFactor;
        }

        cmd.SetGlobalVector("_SourceSize", new Vector4(width, height, 1.0f / width, 1.0f / height));
    }
}
}