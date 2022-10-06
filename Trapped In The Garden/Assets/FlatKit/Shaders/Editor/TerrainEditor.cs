using UnityEditor;
using UnityEngine;

namespace FlatKit {
public class TerrainEditor : StylizedSurfaceEditor, ITerrainLayerCustomUI {
    private class StylesLayer {
        public readonly GUIContent diffuseTexture = new GUIContent("Diffuse");
        public readonly GUIContent colorTint = new GUIContent("Color Tint");
        public readonly GUIContent opacityAsDensity = new GUIContent("Opacity as Density",
            "Enable Density Blend (if unchecked, opacity is used as Smoothness)");
    }

    static StylesLayer s_Styles = null;

    private static StylesLayer styles {
        get {
            if (s_Styles == null) s_Styles = new StylesLayer();
            return s_Styles;
        }
    }

    // Height blend params
    const string kEnableHeightBlend = "_EnableHeightBlend";

    public bool OnTerrainLayerGUI(TerrainLayer terrainLayer, Terrain terrain) {
        var terrainLayers = terrain.terrainData.terrainLayers;

        // Don't use the member field enableHeightBlend as ShaderGUI.OnGUI might not be called if the material UI is folded.
        // heightblend shouldn't be available if we are in multi-pass mode, because it is guaranteed to be broken.
        bool heightBlendAvailable = (terrainLayers.Length <= 4);
        bool heightBlend = heightBlendAvailable && terrain.materialTemplate.HasProperty(kEnableHeightBlend) &&
                           (terrain.materialTemplate.GetFloat(kEnableHeightBlend) > 0);

        terrainLayer.diffuseTexture =
            EditorGUILayout.ObjectField(styles.diffuseTexture, terrainLayer.diffuseTexture, typeof(Texture2D), false) as
                Texture2D;
        TerrainLayerUtility.ValidateDiffuseTextureUI(terrainLayer.diffuseTexture);

        var diffuseRemapMin = terrainLayer.diffuseRemapMin;
        var diffuseRemapMax = terrainLayer.diffuseRemapMax;
        EditorGUI.BeginChangeCheck();

        bool enableDensity = false;
        if (terrainLayer.diffuseTexture != null) {
            var rect = GUILayoutUtility.GetLastRect();
            rect.y += 16 + 4;
            rect.width = EditorGUIUtility.labelWidth + 64;
            rect.height = 16;

            ++EditorGUI.indentLevel;

            var diffuseTint = new Color(diffuseRemapMax.x, diffuseRemapMax.y, diffuseRemapMax.z);
            diffuseTint = EditorGUI.ColorField(rect, styles.colorTint, diffuseTint, true, false, false);
            diffuseRemapMax.x = diffuseTint.r;
            diffuseRemapMax.y = diffuseTint.g;
            diffuseRemapMax.z = diffuseTint.b;
            diffuseRemapMin.x = diffuseRemapMin.y = diffuseRemapMin.z = 0;

            if (!heightBlend) {
                rect.y = rect.yMax + 2;
                enableDensity = EditorGUI.Toggle(rect, styles.opacityAsDensity, diffuseRemapMin.w > 0);
            }

            --EditorGUI.indentLevel;
        }

        diffuseRemapMax.w = 1;
        diffuseRemapMin.w = enableDensity ? 1 : 0;

        if (EditorGUI.EndChangeCheck()) {
            terrainLayer.diffuseRemapMin = diffuseRemapMin;
            terrainLayer.diffuseRemapMax = diffuseRemapMax;
        }

        EditorGUILayout.Space();
        TerrainLayerUtility.TilingSettingsUI(terrainLayer);

        return true;
    }
}
}