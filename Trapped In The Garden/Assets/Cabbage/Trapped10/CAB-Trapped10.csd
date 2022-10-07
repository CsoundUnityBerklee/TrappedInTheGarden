<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped10rev") size(650, 500), guiMode("queue") pluginId("def1")

button  bounds(44, 70, 86, 55) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(70, 128, 27, 28), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(30, 160, 114, 22), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9")
hslider bounds(8, 184, 175, 50) channel("reTrigRate") range(.02, 20, 2, 1, 0.001) text("ReTrig Rate") textColour("white")

hslider bounds(148, 130, 175, 50) channel("dur") range(1, 10, 4, 1, 0.001) text("Dur") textColour("white")

hslider bounds(184, 26, 158, 50) channel("masterLvl") range(0, 1, 0.5, 1, 0.001) text("Master Lvl") textColour("white")
hslider bounds(490, 26, 150, 50) channel("verbLvl") range(0, 1, 0.6, 1, 0.001) text("Verb Lvl") textColour("white")
hslider bounds(342, 26, 150, 50) channel("amp") range(0, 1, 0.5, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)

hslider bounds(324, 130, 160, 52) channel("frq") range(20, 1000, 396, 1, 0.001) text("Freq") textColour("white")
hslider bounds(486, 130, 150, 50) channel("rndFrq") range(0, 400, 130, 1, 0.001) text("RandFreq") textColour("white")

hslider bounds(240, 184, 151, 49) channel("masterRate") range(.5, 2, 1, 1, 0.001) text("MasterRate") textColour("white")
hslider bounds(12, 242, 159, 50) channel("rndRate1") range(0, 200, 200, 1, 0.001) text("RndRate1") textColour("white")
hslider bounds(172, 244, 150, 50) channel("rndRate2") range(0, 200, 180, 1, 0.001) text("RndRate2") textColour("white")
hslider bounds(322, 242, 159, 50) channel("rndRate3") range(0, 200, 120, 1, 0.001) text("RndRate3") textColour("white")
hslider bounds(484, 242, 150, 50) channel("rndRate4") range(0, 200, 160, 1, 0.001) text("RndRate4") textColour("white")

hslider bounds(402, 186, 151, 48) channel("masterDepth") range(.5, 2, 1, 1, 0.001) text("MasterDepth") textColour("white")
hslider bounds(8, 296, 159, 50) channel("rndDepth1") range(0, 100, 50, 1, 0.001) text("RndDpth1") textColour("white")
hslider bounds(174, 294, 150, 50) channel("rndDepth2") range(0, 100, 45, 1, 0.001) text("RndDpth2") textColour("white")
hslider bounds(326, 294, 159, 50) channel("rndDepth3") range(0, 100, 40, 1, 0.001) text("RndDpth3") textColour("white")
hslider bounds(490, 294, 150, 50) channel("rndDepth4") range(0, 100, 60, 1, 0.001) text("RndDpth4") textColour("white")

hslider bounds(260, 78, 161, 50) channel("rvbSend") range(0, 1, .45, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(420, 78, 150, 50) channel("rvbPan") range(.001, 3, .5, 1, 0.001) text("Rvb Pan") textColour("white")

hslider bounds(38, 354, 272, 50) channel("macro1") range(.1, 6, 1, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(38, 406, 272, 50) channel("macro2") range(1, 20, 5, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(326, 354, 272, 55) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(326, 410, 272, 50) channel("macro4") range(.2, 10, 2, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(76, 12, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1") text("init", "lower + rough", "rumble", "rumble + pitches", "swirling s an h", "high swirling", "Low + Slower")
filebutton bounds(12, 12, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(12, 40, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
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

ksmps = 32
nchnls = 2
0dbfs = 1

garvb  init  0

giFun1 ftgen 1, 0, 8192, 10, 1
giFun2 ftgen 2, 0, 8192, 10, 1, .8, 0, .6, 0, .4, 0, .01
giFun3 ftgen 3, 0, 8192, 10, 1,  0, .5, .2, 0, .4, .3, 0, .01
giFun4 ftgen 4, 0, 8192, 10, 1,  0, .9, 0, 0, .8, 0, .7, 0, .4, 0, .2, 0, .01

instr 1
    iDur = chnget:i("dur") 
    iFrq = chnget:i("frq") + rnd(chnget:i("rndFrq"))
    iAmp = chnget:i("amp")

    kTrig chnget "trigger"
    kReTrig chnget "reTrigger"

    if kReTrig == 1 then
        kRndH randh chnget:k("reTrigRate")*chnget:k("macro4")*0.4, 4
        kTrig metro chnget:k("reTrigRate")*chnget:k("macro4")+kRndH
    endif    
    
    if changed(kTrig) == 1 then
        event "i", "Trapped10", 0, iDur, iFrq, iAmp 
    endif
endin

instr  Trapped10

iDur        = chnget:i("dur")
iAmp        = chnget:i("amp")              
iFrq        = chnget:i("frq") + rnd(chnget:i("rndFrq"))

kMstrRate   = chnget:k("masterRate")
kRndRate1   = chnget:k("rndRate1")
kRndRate2   = chnget:k("rndRate2")
kRndRate3   = chnget:k("rndRate3")
kRndRate4   = chnget:k("rndRate4")

kMstrDpth   = chnget:k("masterDepth")
kRndDpth1   = chnget:k("rndDepth1")
kRndDpth2   = chnget:k("rndDepth2")
kRndDpth3   = chnget:k("rndDepth3")
kRndDpth4   = chnget:k("rndDepth4")
                                                                                                                                             
kRnd1          randh     kMstrDpth * kRndDpth1, kMstrRate * kRndRate1, .1                     
kRnd2          randh     kMstrDpth * kRndDpth2, kMstrRate * kRndRate2, .2             
kRnd3          randh     kMstrDpth * kRndDpth3, kMstrRate * kRndRate3, .3            
kRnd4          randh     kMstrDpth * kRndDpth4, kMstrRate * kRndRate4, .4     

kEnv           linen     iAmp, iDur * .1, iDur, iDur * .8                        

a1             oscil     kEnv, (iFrq + kRnd1) * chnget:k("macro1"), 1, .2             
a2             oscil     kEnv * .91, ((iFrq + .04) + kRnd2) * chnget:k("macro1"), 2, .3
a3             oscil     kEnv * .85, ((iFrq + .06) + kRnd3) * chnget:k("macro1"), 3, .5
a4             oscil     kEnv * .95, ((iFrq + .09) + kRnd4) * chnget:k("macro1"), 4, .8

kgate         transeg   1, iDur, 0, 0 

aL              =  (a1 + a3) * kgate
aR              =  (a2 + a4) * kgate

aFltL         moogladder2  aL, 200 * chnget:k("macro2"), .8
aFltR         moogladder2  aR, 200 * chnget:k("macro2"), .8

amix            =  aFltL + aFltR

               outs      aFltL * chnget:k("masterLvl") * chnget:k("macro3"), aFltR * chnget:k("masterLvl") * chnget:k("macro3")             
garvb          =         garvb + (amix * chnget:k("rvbSend") * (1-chnget:k("macro3"))) 
               endin
   
               instr     Reverb 
               denorm    garvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
asig           reverb2   garvb, 4.1, .7
               outs      (asig * k2) * chnget:k("verbLvl") * chnget:k("masterLvl") * chnget:k("macro3"), ((asig * k3) * (-1)) * chnget:k("verbLvl") * chnget:k("masterLvl") * chnget:k("macro3")
garvb          =         0
               endin

</CsInstruments>
<CsScore>
;causes Csound to run for about 7000 years...
f0 z
;starts instrument 1 and runs it for a week
i1 0 [60*60*24*7] 
i "Reverb" 0 [60*60*24*7]  
</CsScore>
</CsoundSynthesizer>