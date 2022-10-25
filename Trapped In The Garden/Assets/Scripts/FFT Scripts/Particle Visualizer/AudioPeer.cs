using UnityEngine;
using System.Collections;

[RequireComponent (typeof (AudioSource))]
public class AudioPeer : MonoBehaviour {
	AudioSource _audioSource;
	 public static float[] _samplesLeft = new float[512];
	public static float[] _samplesRight = new float[512];

	 float[] _freqBand = new float[8];
	 float[] _bandBuffer = new float[8];
	float[] _bufferDecrease = new float[8];

	float[] _freqBandHighest = new float[8];
	public static float[] _audioBand = new float[8];
	public static float[] _audioBandBuffer = new float[8];

	public static float _Amplitude, _AmplitudeBuffer;
	float _AmplitudeHighest;
	private float _audioProfile;

	public enum _channel {Stereo, Left, Right};
	public _channel channel = new _channel ();

	// Use this for initialization
	void Start () {
		_audioSource = GetComponent<AudioSource> ();
        _audioProfile = 0.5f;
		AudioProfile (_audioProfile);
        _AmplitudeHighest = 1;

    }
		
	// Update is called once per frame
	void Update () {
		GetSpectrumAudioSource ();
		MakeFrequencyBands ();
		BandBuffer ();
		CreateAudioBands ();
		GetAmplitude ();
	}
		
	void AudioProfile(float audioProfile)
	{
		for (int i = 0; i < 8; i++) {
			_freqBandHighest [i] = audioProfile;
		}
	}
		
	void GetAmplitude()
	{
		float _CurrentAmplitude = 0;
		float _CurrentAmplitudeBuffer = 0;
		for (int i = 0; i < 8; i++) {
			_CurrentAmplitude += _audioBand [i];
			_CurrentAmplitudeBuffer += _audioBandBuffer [i];
		}
		if (_CurrentAmplitude > _AmplitudeHighest) {
			_AmplitudeHighest = _CurrentAmplitude;
		}
		_Amplitude = _CurrentAmplitude / _AmplitudeHighest;
		_AmplitudeBuffer = _CurrentAmplitudeBuffer / _AmplitudeHighest;
	}

	void CreateAudioBands()
	{
		for (int i = 0; i < 8; i++) 
		{
			if (_freqBand [i] > _freqBandHighest [i]) {
				_freqBandHighest [i] = _freqBand [i];
			}
			_audioBand [i] = (_freqBand [i] / _freqBandHighest [i]);
			_audioBandBuffer [i] = (_bandBuffer [i] / _freqBandHighest [i]);
		}
	}

	void GetSpectrumAudioSource()
	{
		_audioSource.GetSpectrumData(_samplesLeft, 0, FFTWindow.Blackman);
		_audioSource.GetSpectrumData(_samplesRight, 1, FFTWindow.Blackman);
	}
		

	void BandBuffer()
	{
		for (int g = 0; g < 8; ++g) {
			if (_freqBand [g] > _bandBuffer [g]) {
				_bandBuffer [g] = _freqBand [g];
				_bufferDecrease [g] = 0.005f;
			}

			if (_freqBand [g] < _bandBuffer [g]) {
				_bandBuffer[g] -= _bufferDecrease [g];
				_bufferDecrease [g] *= 1.2f;
			}

		}
	}
		
	void MakeFrequencyBands()
	{
		int count = 0;

		for (int i = 0; i < 8; i++) {


			float average = 0;
			int sampleCount = (int)Mathf.Pow (2, i) * 2;

			if (i == 7) {
				sampleCount += 2;
			}
			for (int j = 0; j < sampleCount; j++) {
				if (channel == _channel.Stereo) {
					average += (_samplesLeft [count] + _samplesRight [count]) * (count + 1);
				}
				if (channel == _channel.Left) {
					average += _samplesLeft [count] * (count + 1);
				}
				if (channel == _channel.Right) {
					average += _samplesRight [count] * (count + 1);
				}
					count++;

			}

			average /= count;

			_freqBand [i] = average * 10;

		}
	}
	public float getAmplitudeBuffer()
	{
		return _AmplitudeBuffer;
	}
	public float getAmplitude()
	{
		return _Amplitude; 
	}
	public float[] getAudioBandBuffer()

	{
		return _audioBandBuffer;
	}

}

