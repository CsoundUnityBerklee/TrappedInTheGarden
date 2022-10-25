using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioFlowfield : MonoBehaviour
{
    NoiseFlowField_2 _noiseflowfield;
    public AudioPeer _audioPeer;

    public bool _useSpeed;
    public Vector2 _moveSpeedMinMax, _rotateSpeedaMinMax;

    public bool _useScale;
    public Vector2 _ScaleMinMax;
    public float scale = 0;

    //MATERIAL
    public Material _material;
    private Material[] _audioMaterial;
    public bool _useColor1;
    public Gradient _gradient1;
    private Color[] _color1;
    [Range(0f,1f)]
    public float _colorThreshold1;
    public float _colorMultiplier1;
    public string _colorName1;



    public bool _useColor2;
    public Gradient _gradient2;
    private Color[] _color2;
    [Range(0f, 1f)]
    public float _colorThreshold2;
    public float _colorMultiplier2;
    public string _colorName2;

    public bool _useColor3;
    public Gradient _gradient3;
    private Color[] _color3;
    [Range(0f, 1f)]
    public float _colorThreshold3;
    public float _colorMultiplier3;
    public string _colorName3;


    void Start()
    {
        _noiseflowfield = GetComponent<NoiseFlowField_2>();
        _audioMaterial = new Material[8];
        _color1 = new Color[8];
        _color2 = new Color[8];
        _color3 = new Color[8];
        for (int i = 0; i < 8; i++)
        {
            _color1[i] =_gradient1.Evaluate((1f / 8f) * i);
            _color2[i] =_gradient2.Evaluate((1f / 8f) * i);
            _color3[i] = _gradient3.Evaluate((1f / 8f) * i);

            _audioMaterial[i] = new Material(_material);

        }

        int countBand = 0;
        for (int i = 0; i < _noiseflowfield._amountOfParticles; i++)
        {
            int band = countBand % 8;
            _noiseflowfield._particleMeshRenderer[i].material = _audioMaterial[band];
            _noiseflowfield._particleList[i]._audioBand = band;
            countBand++;
        }
    }

    
    void Update()
    {
        switch((_noiseflowfield.getColor()))
        {
            case 0:
                _useColor2 = true;
                _useColor1 = false;
                _useColor3 = false;
                break;
            case 1:
                _useColor2 = false;
                _useColor1 = false;
                _useColor3 = true;
                break;
            case 2:
                _useColor2 = false;
                _useColor1 = true;
                _useColor3 = false;
                break;

        }

        if (_useSpeed)
        {
            
            _noiseflowfield._particleMoveSpeed= Mathf.Lerp(_moveSpeedMinMax.x,_moveSpeedMinMax.y,_audioPeer.getAmplitudeBuffer());
            _noiseflowfield._particleRotateSpeed = Mathf.Lerp(_rotateSpeedaMinMax.x, _rotateSpeedaMinMax.y, _audioPeer.getAmplitudeBuffer());

        }
        for (int i = 0; i < _noiseflowfield._amountOfParticles; i++)
        {
            if (_useScale)
            {
                 scale = Mathf.Lerp(_ScaleMinMax.x, _ScaleMinMax.y, _audioPeer.getAudioBandBuffer()[_noiseflowfield._particleList[i]._audioBand]);
                _noiseflowfield._particleList[i].transform.localScale = new Vector3(scale, scale, scale);
            }
        }
        for (int i = 0; i < 8; i++)
        {
            if (_useColor1)
            {
                if (_audioPeer.getAudioBandBuffer()[i] > _colorThreshold1)
                {
                    _audioMaterial[i].SetColor(_colorName1, _color1[i] * _audioPeer.getAudioBandBuffer()[i] * _colorMultiplier1);
                }
                else
                {
                    _audioMaterial[i].SetColor(_colorName1, _color1[i] * 0f);
                }
            }
            if (_useColor2)
            {
                if (_audioPeer.getAudioBandBuffer()[i] > _colorThreshold2)
                {
                    _audioMaterial[i].SetColor(_colorName2, _color2[i] * _audioPeer.getAudioBandBuffer()[i] * _colorMultiplier2);
                }
                else
                {
                    _audioMaterial[i].SetColor(_colorName2, _color2[i] * 0f);
                }
            }
            if (_useColor3)
            {
                if (_audioPeer.getAudioBandBuffer()[i] > _colorThreshold3)
                {
                    _audioMaterial[i].SetColor(_colorName3, _color3[i] * _audioPeer.getAudioBandBuffer()[i] * _colorMultiplier3);
                }
                else
                {
                    _audioMaterial[i].SetColor(_colorName3, _color3[i] * 0f);
                }
            }

        }
    }
}
