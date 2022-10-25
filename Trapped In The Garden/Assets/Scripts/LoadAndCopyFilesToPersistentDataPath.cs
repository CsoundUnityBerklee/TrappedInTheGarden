using System;
using System.Collections;
using System.IO;
using UnityEngine;
using UnityEngine.Networking;

namespace Csound.LoadFiles
{
    /// <summary>
    /// Loads different kind of files and copies them into the Persistent Data Path so that they can be found by Csound
    /// </summary>
    public class LoadAndCopyFilesToPersistentDataPath : MonoBehaviour
    {
        [Tooltip("The names of the plugins to copy from Resources to the Persistent Data Path folder. " +
            "Don't specify the extension. The extension will be added to the copied files depending on the platform")]
        [SerializeField] private string[] _pluginsNames;
        [Tooltip("Those files will be read from the StreamingAssets folder")]
        [SerializeField] private string[] _streamingAssetsFiles;
        [Tooltip("Those files will be read from Resources folders")]
        [SerializeField] private AdditionalFileInfo[] _additionalFiles;

        [Tooltip("Ensure this CsoundUnity GameObject is inactive when hitting play, " +
            "otherwise the CsoundUnity initialization will run. " +
            "Setting the Environment Variables on a running Csound instance can have unintended effects.")]
        public CsoundUnity CsoundUnity;

        void Awake()
        {
            Debug.Log($"{Time.time} LOAD PLUGINS AND FILES AWAKE");
            foreach (var pluginName in _pluginsNames)
            {
                Debug.Log($"COPYING PLUGIN: {pluginName}");
                var dir = Application.persistentDataPath;
                var pluginPath = string.Empty;
                var destinationPath = string.Empty;
#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
                destinationPath = Path.Combine(dir, pluginName + ".dll");
                pluginPath = Path.Combine("Win", pluginName);
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX || UNITY_IOS
                destinationPath = Path.Combine(dir, "lib" + pluginName + ".dylib");
                pluginPath = Path.Combine("MacOS", "lib" + pluginName);
#elif UNITY_ANDROID
                destinationPath = Path.Combine(dir, "lib" + pluginName + ".so");
                pluginPath = Path.Combine("Android", "lib" + pluginName);
#endif
                Debug.Log($"FILE EXISTS? {File.Exists(destinationPath)}");
                if (!File.Exists(destinationPath))
                {
                    Debug.Log($"Loading plugin at path: {pluginPath}");
                    var plugin = Resources.Load<TextAsset>(pluginPath);
                    Debug.Log($"Loaded bytes: {plugin.bytes.Length}");
                    Debug.Log($"Writing plugin file at path: {destinationPath}");
                    WriteFile(plugin.bytes, destinationPath);
                }
            }

            foreach (var streamingAssetFile in _streamingAssetsFiles)
            {
                var destinationPath = Path.Combine(Application.persistentDataPath, streamingAssetFile);
                LoadAndCopyAudioFileFromStreamingAssets(streamingAssetFile, destinationPath);
            }

            foreach (var additionalFile in _additionalFiles)
            {
                var dir = Path.Combine(Application.persistentDataPath, additionalFile.Directory);

                if (!Directory.Exists(dir))
                    Directory.CreateDirectory(dir);

                var filePath = Path.Combine(additionalFile.Directory, additionalFile.FileName + "." + additionalFile.Extension);
                var destinationPath = Path.Combine(dir, additionalFile.FileName + "." + additionalFile.Extension);

                Debug.Log($"COPYING ADDITIONAL FILE: {additionalFile.FileName}, destinationPath: {destinationPath}");
                if (!File.Exists(destinationPath))
                {
                    LoadAndCopyGenericFile(filePath, destinationPath);
                }
            }

            // activate CsoundUnity!
            CsoundUnity.gameObject.SetActive(true);
        }

        private void LoadAndCopyAudioFileFromStreamingAssets(string origin, string destination)
        {
            var path = Path.Combine(Application.streamingAssetsPath, origin);
#if UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
            var bytes = File.ReadAllBytes(path);
            WriteFile(bytes, destination);
#else
            StartCoroutine(GetRequest(path, (bytes) =>
            {
                WriteFile(bytes, destination);
            }));
#endif
        }

        IEnumerator GetRequest(string uri, Action<byte[]> onBytesLoaded)
        {
            using (var req = UnityWebRequest.Get(uri))
            {
                yield return req.SendWebRequest();

                switch (req.result)
                {
                    case UnityWebRequest.Result.ConnectionError:
                    case UnityWebRequest.Result.DataProcessingError:
                        Debug.LogError($"Error: {req.error}");
                        break;
                    case UnityWebRequest.Result.ProtocolError:
                        Debug.LogError($"HTTP Error: {req.error}");
                        break;
                    case UnityWebRequest.Result.Success:
                        Debug.Log($"{req.downloadHandler.data.Length} bytes read");
                        onBytesLoaded?.Invoke(req.downloadHandler.data);
                        break;
                }
            }
        }

        // this doesn't work properly since it doesn't maintain the header of the audio file, meaning that the file is not readable
        private static void LoadAndCopyAudioFileFromResources(string origin, string destination)
        {
            Debug.Log($"LoadAndCopyAudioFile from {origin} to {destination}");
            var pathWithoutExtension = Path.ChangeExtension(origin, null);
            var audioClip = Resources.Load<AudioClip>(pathWithoutExtension);
            var bytes = GetClipData(audioClip);
            // TODO Add a way to write the header too
            WriteFile(bytes, destination);
        }

        private static void LoadAndCopyGenericFile(string origin, string destination)
        {
            var pathWithoutExtension = Path.ChangeExtension(origin, null);
            var textAsset = Resources.Load<TextAsset>(pathWithoutExtension);
            WriteFile(textAsset.bytes, destination);
        }

        private static byte[] GetClipData(AudioClip audioClip)
        {
            var data = new float[audioClip.samples * audioClip.channels];
            audioClip.GetData(data, 0);
            var bytes = new byte[data.Length * 4];
            Buffer.BlockCopy(data, 0, bytes, 0, bytes.Length);
            return bytes;
        }

        private static void WriteFile(byte[] bytes, string destination)
        {
            Debug.Log($"Writing file ({bytes.Length} bytes) at path: {destination}");
            Stream s = new MemoryStream(bytes);
            BinaryReader br = new BinaryReader(s);
            var dir = Path.GetDirectoryName(destination);
            if (!Directory.Exists(dir))
            {
                Directory.CreateDirectory(dir);
            }
            using (BinaryWriter bw = new BinaryWriter(File.Open(destination, FileMode.OpenOrCreate)))
            {
                bw.Write(br.ReadBytes(bytes.Length));
            }
        }

        [Serializable]
        public class AdditionalFileInfo
        {
            public string Directory;
            public string FileName;
            public string Extension;
        }
    }
}