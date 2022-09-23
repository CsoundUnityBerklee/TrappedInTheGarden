; This will play all bird calls consecutively
<CsoundSynthesizer>
<CsOptions>
-o dac -d --messagelevel=2
</CsOptions>
; ==============================================
<CsInstruments>

sr	=	48000
ksmps	=	1
nchnls	=	2
0dbfs	=	1

#include "aves.inc"

schedule("Play_birds", 0, 125)

</CsInstruments>
; ==============================================
<CsScore>
</CsScore>
</CsoundSynthesizer>
