<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped05rev") size(680, 660), guiMode("queue") pluginId("def1")

button  bounds(96, 118, 86, 55) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(124, 176, 27, 31), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(100, 212, 80, 18), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9") alpha(0.99)
hslider bounds(60, 234, 175, 50) channel("reTrigRate") range(0.1, 6, 1, 0.5, 0.001) text("ReTrig Rate") textColour(255, 255, 255, 255)

hslider bounds(374, 58, 175, 50) channel("dur") range(2, 10, 5, 1, 0.001) text("Dur") textColour("white")

hslider bounds(356, 4, 200, 50) channel("masterLvl") range(0, 1, 0.7, 1, 0.001) text("Master Lvl") textColour("white")
hslider bounds(308, 166, 150, 50) channel("amp") range(0, .8, 0.5, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)

hslider bounds(296, 222, 160, 52) channel("frq") range(20, 500, 150, 1, 0.001) text("Freq") textColour("white")
hslider bounds(476, 220, 150, 50) channel("rndFrq") range(1, 5, 2, 1, 0.001) text("RandFreq") textColour("white")

hslider bounds(464, 166, 160, 52) channel("pan") range(0.1, 1, 1, 1, 0.001) text("Synth Pan") textColour(255, 255, 255, 255)

hslider bounds(300, 326, 159, 50) channel("modFrq") range(10, 100, 10, 1, 0.001) text("Mod Frq") textColour("white")
hslider bounds(478, 328, 150, 50) channel("modAmp") range(100, 1000, 500, 1, 0.001) text("Mod Amp") textColour("white")
hslider bounds(40, 382, 178, 50) channel("modNdx") range(1, 20, 12, 1, 0.001) text("Mod Indx") textColour("white")

hslider bounds(224, 384, 214, 50) channel("mstrModRat") range(1, 20, 12, 1, 0.001) text("MastrModRate") textColour("white")
hslider bounds(444, 384, 208, 50) channel("mstrModDpth") range(1, 20, 1, 1, 0.001) text("MastrModDpth") textColour("white")

hslider bounds(298, 274, 159, 50) channel("carRat") range(1, 10, 1, 1, 0.001) text("Car Ratio") textColour("white")
hslider bounds(476, 270, 150, 55) channel("modRat") range(1, 10, 1, 1, 0.001) text("Mod Ratio") textColour("white")

hslider bounds(298, 112, 161, 49) channel("rvbSend") range(0, 1, .5, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(466, 110, 150, 50) channel("rvbPan") range(.01, 34, 25, 1, 0.001) text("Rvb Pan") textColour("white")

hslider bounds(62, 460, 272, 50) channel("macro1") range(.1, 4, 1, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(62, 512, 272, 50) channel("macro2") range(1, 20, 10, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(336, 460, 272, 50) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(336, 512, 272, 50) channel("macro4") range(.4, 10, 4, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(100, 12, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1") text("init", "high Drop", "rise up", "ripping", "riseUp2", "another")
filebutton bounds(36, 12, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(36, 40, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
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

giFn1 ftgen 1, 0, 8192, 10, 1

instr 1
    iDur = chnget:i("dur")
 
    iFrq = chnget:i("frq")*rnd(chnget:i("rndFrq"))
    iAmp = chnget:i("amp")
    kTrig chnget "trigger"
    kReTrig chnget "reTrigger"
        if kReTrig == 1 then
            kRndH randh chnget:k("reTrigRate")*chnget:k("macro4") * .4, 4
            kTrig metro chnget:k("reTrigRate")*chnget:k("macro4") + kRndH
        endif

        if changed(kTrig) == 1 then
            event "i", "Trapped05", 0, iDur, iFrq, iAmp 
        endif
endin

instr Trapped05

iDur        = chnget:i("dur")
iAmp        = chnget:i("amp")             
iFrq        = chnget:i("frq")*rnd(chnget:i("rndFrq"))
iPan        = chnget:i("pan")
iModFrq     = chnget:i("modFrq")
iModAmp     = chnget:i("modAmp")
iCarRat     = chnget:i("carRat")
iModRat     = chnget:i("modRat")
kModNdx     = chnget:k("modNdx")
kMstrRndDp  = chnget:k("mstrModDpth")
kMastRndRt  = chnget:k("mstrModRat")
                                                                                    
kCarRat        line      iCarRat, iDur, 1                     
kModRat        line      1, iDur, iModRat                      
kModAmp        expon     2, iDur, iModAmp                   
kModFrq        linseg    0, iDur * .8, 8, iDur * .2, 8     
kIndx          randh     kModAmp * kMstrRndDp, kModFrq * kMastRndRt                                        
kMod           oscil     kModAmp, kModFrq  * chnget:k("macro1"), 1, .3    

kEnv           linen     iAmp, .03, iDur, .2     
aSig           foscil    kEnv*.4, (iFrq + kMod) * chnget:k("macro1"), kCarRat, kModRat, kIndx, 1

kpan           linseg    int(iPan), iDur * .7, frac(iPan), iDur * .3, int(iPan)

aFlt         moogladder2  aSig, 200 * chnget:k("macro2"), .8

               outs      (aFlt*.5) * kpan * chnget:k("masterLvl")*chnget:k("macro3"), (aFlt*.5) *  (1 - kpan) * chnget:k("masterLvl")*chnget:k("macro3")
                                     
garvb          =         garvb + ((aFlt *.6) * chnget:k("rvbSend") * (1-chnget:k("macro3")))  
               endin

               instr     Reverb 
               denorm    garvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
asig           reverb    garvb*.5, 3.1
               outs      (asig * k2) * chnget:k("masterLvl")*chnget:k("macro3"), ((asig * k3) * (-1)) * chnget:k("masterLvl")*chnget:k("macro3")
garvb          =         0
               endin

</CsInstruments>
<CsScore>
f0 z
i1 0 [60*60*24*7] 
i "Reverb" 0 [60*60*24*7]  
</CsScore>
</CsoundSynthesizer>