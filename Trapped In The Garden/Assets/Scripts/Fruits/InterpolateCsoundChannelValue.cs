using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class InterpolateCsoundChannelValue
{
    public static IEnumerator LerpChannelValue(CsoundUnity csound, string channel, float duration, float delay, float targetValue)
    {
        yield return new WaitForSeconds(delay);

        float initialValue = (float)csound.GetChannel(channel);
        float currentTime = 0;

        while (currentTime < duration)
        {
            currentTime += Time.deltaTime;
            csound.SetChannel(channel, Mathf.Lerp(initialValue, targetValue, currentTime / duration));
            yield return null;
        }
        yield break;
    }
}
