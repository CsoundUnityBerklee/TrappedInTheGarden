<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped03rev") size(700, 500), guiMode("queue") pluginId("def1")

button  bounds(66, 128, 86, 55) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(92, 192, 27, 31), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(68, 230, 80, 18), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9") alpha(0.99)
hslider bounds(16, 260, 175, 50) channel("reTrigRate") range(0.1, 6, 1, 0.5, 0.001) text("ReTrig Rate") textColour(255, 255, 255, 255)

hslider bounds(44, 68, 168, 46) channel("dur") range(4, 12, 6, 1, 0.001) text("Dur") textColour(255, 255, 255, 255)

hslider bounds(264, 12, 158, 50) channel("masterLvl") range(0, 1, 0.6, 1, 0.001) text("Master Lvl") textColour(255, 255, 255, 255)
hslider bounds(434, 10, 150, 50) channel("amp") range(0, 1, 0.6, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)

hslider bounds(184, 124, 160, 52) channel("frq") range(30, 1000, 800, 1, 0.001) text("Frq") textColour(255, 255, 255, 255)
hslider bounds(350, 124, 160, 52) channel("rndFrq") range(2, 100, 100, 1, 0.001) text("RandFrq") textColour(255, 255, 255, 255)
hslider bounds(518, 124, 160, 52) channel("gliss") range(0.25, 4, 0.9, 1, 0.001) text("FrqSweep") textColour(255, 255, 255, 255)

hslider bounds(270, 188, 151, 48) channel("masterRate") range(0.15, 8, 1, 1, 0.001) text("MasterRate") textColour(255, 255, 255, 255)
hslider bounds(198, 242, 159, 50) channel("rndRate1") range(10, 100, 20, 1, 0.001) text("RndRate1") textColour(255, 255, 255, 255)
hslider bounds(364, 244, 150, 50) channel("rndRate2") range(10, 100, 30, 1, 0.001) text("RndRate2") textColour(255, 255, 255, 255)
hslider bounds(522, 244, 150, 50) channel("rndRate3") range(10, 100, 40, 1, 0.001) text("RndRate3") textColour(255, 255, 255, 255)

hslider bounds(432, 188, 151, 48) channel("masterDepth") range(0.15, 8, 1, 1, 0.001) text("MasterDepth") textColour(255, 255, 255, 255)
hslider bounds(198, 300, 159, 50) channel("rndDep1") range(1, 150, 123, 1, 0.001) text("RndDpth1") textColour(255, 255, 255, 255)
hslider bounds(364, 302, 150, 50) channel("rndDep2") range(5, 260, 234, 1, 0.001) text("RndDpth2") textColour(255, 255, 255, 255)
hslider bounds(522, 302, 150, 50) channel("rndDep3") range(6, 390, 145, 1, 0.001) text("RndDpth3") textColour(255, 255, 255, 255)

hslider bounds(262, 64, 161, 50) channel("rvbSend") range(0, 0.7, 0.24, 1, 0.001) text("Rvb Send") textColour(255, 255, 255, 255)
hslider bounds(434, 64, 150, 50) channel("rvbPan") range(0.1, 24, 10, 1, 0.001) text("Rvb Pan") textColour(255, 255, 255, 255)

hslider bounds(74, 362, 272, 50) channel("macro1") range(.1, 3, .2, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(74, 414, 272, 50) channel("macro2") range(1, 20, 5, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(356, 360, 272, 50) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(356, 416, 272, 50) channel("macro4") range(.4, 10, 2, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(108, 10, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1") text("slow blips1", "slow rise", "high rise", "low burble", "lower less turbulent", "low and slow", "ramping up", "rising beeps", "descending noisy ", "low and rough")
filebutton bounds(44, 10, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(44, 38, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
</Cabbage>

<CsoundSynthesizer>

<CsOptions>
-n -dm0
</CsOptions>

; macro1 = Pitch (on Y axis)
; macro2 = Filter or Spectral Content (on X asis)
; macro3 = Volume and Verb (on Z axis)
; macro4 = Rate (on Rotation)

<CsInstruments>
ksmps = 64
nchnls = 2
0dbfs = 1

garvb  init  0

giFn01 ftgen 1, 0, 8192, 10, 1
giFn16 ftgen 16, 0, 2048, 9, 1, 3, 0, 3, 1, 0, 6, 1, 0

maxalloc "Trapped03", 25


instr 1
    iDur = chnget:i("dur")
 
    iFrq = chnget:i("frq") + rnd(chnget:i("rndFrq"))
    iAmp = chnget:i("amp")
    
    kTrig   chnget "trigger"
    kReTrig chnget "reTrigger"
        if kReTrig == 1 then
            kRndH randh chnget:k("reTrigRate")*chnget:k("macro4") * .4, 4
            kTrig metro chnget:k("reTrigRate")*chnget:k("macro4") + kRndH
        endif

        if changed(kTrig) == 1 then
            event "i", "Trapped03", 0, iDur, iFrq, iAmp 
        endif
endin


instr     Trapped03

iDur       = chnget:i("dur")
iAmp       = chnget:i("amp") 
iAmp       = iAmp * .3            
kFrq       = chnget:k("frq") + rnd(chnget:i("rndFrq"))

kMstrRate  = chnget:k("masterRate")
iRndRate1  = chnget:i("rndRate1")
iRndRate2  = chnget:i("rndRate2")
iRndRate3  = chnget:i("rndRate3")
kMstrDpth  = chnget:k("masterDepth")
iRndDep1   = chnget:i("rndDep1")
iRndDep2   = chnget:i("rndDep2")
iRndDep3   = chnget:i("rndDep3")

iGlis      = chnget:i("gliss")

kRvbSnd    = chnget:k("rvbSend")                                                                                                                                                                             

kRndDp1        transeg    10, iDur, iRndDep1, 1
kRate1         transeg    20, iDur, iRndRate1, 1

kRndDp2        transeg    20, iDur, iRndDep2, 2 
kRate2         transeg    80, iDur, iRndRate2, 2
           
kRndDp3        transeg    40, iDur, iRndDep3, 3   
kRate3         transeg    50, iDur, iRndRate3, 3

kGlis          transeg    1, iDur, 0, iGlis

kEnv1          transeg   0, iDur * .2, 0, iAmp, iDur * .8, 0, 0
kRndH1         randh     kRndDp1 * kMstrDpth, kRate1 * kMstrRate, .5
aSig1          buzz      kEnv1, (kFrq + kRndH1) * kGlis * chnget:k("macro1"), kRndH1 * chnget:k("macro2"), 1

kEnv2          transeg   0, iDur * .4, 0, iAmp, iDur * .6, 0, 0
kRndH2         randh     kRndDp2 * kMstrDpth, kRate2 * kMstrRate
aSig2          buzz      kEnv2 , ((kFrq * 1.1) + kRndH2) * kGlis * chnget:k("macro1"), kRndH2 * chnget:k("macro2"), 1

kEnv3          transeg   0, iDur * .6, 0, iAmp, iDur * .4, 0, 0
kRndH3         randh     kRndDp3 * kMstrDpth, kRate3 * kMstrRate, .2
aSig3          buzz      kEnv3, ((kFrq * .99) + kRndH3) * kGlis * chnget:k("macro1"), kRndH3 * chnget:k("macro2"), 1


kgate    transeg  1, iDur, 0, 1

aL = (aSig2 + aSig3) * kgate
aR = (aSig1 + aSig2) * kgate

aSig = (aL + aR)

aFlt         moogladder2  aSig, 200 * chnget:k("macro2"), .8

aMix           =        aFlt * kgate

             outs      aMix * (chnget:k("masterLvl")*chnget:k("macro3")), aMix * (chnget:k("masterLvl")*chnget:k("macro3"))
           
garvb          =         garvb + (aMix * (chnget:k("rvbSend"))*(1-chnget:k("macro3")))  
 
               endin


               instr     Reverb 
               denorm    garvb
iRvbTime       =         4 
kgate          transeg   1, chnget:i("iDur") + iRvbTime, 0, 0
kSpeed         transeg   1, chnget:i("iDur") * .6, 0, 1, chnget:i("iDur") * .4, 0, 3                   
k1             oscil     .5, chnget:k("rvbPan") * kSpeed, 1
k2             =         .5 + k1
k3             =         1 - k2
asig           reverb    garvb, iRvbTime
;               outs      .5 * (asig * k2) * chnget:k("masterLvl"), .5 * ((asig * k3) * (-1)) * chnget:k("masterLvl")
              outs      (asig * k2) * (chnget:k("masterLvl")*chnget:k("macro3")), ((asig * k3) * (-1)) * (chnget:k("masterLvl")*chnget:k("macro3"))

garvb          =         0
               endin

</CsInstruments>

<CsScore>
f0 z

i1 0 [60*60*24*7] 
i "Reverb" 0 [60*60*24*7]  
</CsScore>

</CsoundSynthesizer>