<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped05rev") size(680, 560), guiMode("queue") pluginId("def1")

button  bounds(114, 174, 86, 55) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(146, 232, 27, 31), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(122, 266, 81, 16), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9") alpha(0.99)
hslider bounds(78, 286, 175, 50) channel("reTrigRate") range(0.1, 6, 1, 0.5, 0.001) text("ReTrig Rate") textColour(255, 255, 255, 255)

hslider bounds(66, 58, 175, 50) channel("dur") range(2, 10, 5, 1, 0.001) text("Dur") textColour("white")

hslider bounds(72, 6, 158, 50) channel("masterLvl") range(0, 1, 0.7, 1, 0.001) text("Master Lvl") textColour("white")
hslider bounds(296, 60, 161, 50) channel("amp") range(0, 1, 0.7, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)

hslider bounds(298, 112, 160, 52) channel("frq") range(20, 500, 150, 1, 0.001) text("Freq") textColour("white")
hslider bounds(462, 114, 160, 50) channel("rndFrq") range(1, 5, 2, 1, 0.001) text("RandFreq") textColour("white")

hslider bounds(462, 60, 160, 52) channel("pan") range(.1, 1, 1, 1, 0.001) text("Synth Pan") textColour("white")

hslider bounds(300, 214, 159, 50) channel("modFrq") range(10, 100, 10, 1, 0.001) text("Mod Frq") textColour("white")
hslider bounds(464, 214, 159, 50) channel("modAmp") range(100, 1000, 500, 1, 0.001) text("Mod Amp") textColour("white")
hslider bounds(390, 264, 150, 50) channel("modNdx") range(1, 20, 12, 1, 0.001) text("Mod Indx") textColour("white")

hslider bounds(302, 314, 159, 52) channel("mstrModRat") range(1, 20, 12, 1, 0.001) text("MastrModRate") textColour("white")
hslider bounds(468, 314, 159, 52) channel("mstrModDpth") range(1, 20, 1, 1, 0.001) text("MastrModDpth") textColour("white")

hslider bounds(298, 164, 159, 50) channel("carRat") range(1, 10, 1, 1, 0.001) text("Car Ratio") textColour(255, 255, 255, 255)
hslider bounds(462, 164, 163, 50) channel("modRat") range(1, 10, 1, 1, 0.001) text("Mod Ratio") textColour("white")

hslider bounds(296, 8, 161, 49) channel("rvbSend") range(0, 1, .5, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(462, 10, 161, 50) channel("rvbPan") range(.01, 34, 25, 1, 0.001) text("Rvb Pan") textColour("white")

combobox bounds(138, 118, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1") text("init", "high Drop", "rise up", "ripping", "riseUp2", "another")
filebutton bounds(74, 118, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(74, 146, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
</Cabbage>

<CsoundSynthesizer>

<CsOptions>
-n -dm0
</CsOptions>

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
kMod           oscil     kModAmp, kModFrq, 1, .3    

kEnv           linen     iAmp, .03, iDur, .2     
aSig             foscil    kEnv, iFrq + kMod, kCarRat, kModRat, kIndx, 1

kpan           linseg    int(iPan), iDur * .7, frac(iPan), iDur * .3, int(iPan)

               outs      aSig * kpan * chnget:k("masterLvl"), aSig *  (1 - kpan) * chnget:k("masterLvl")
                                     
garvb          =         garvb + (aSig * chnget:k("rvbSend"))  
               endin

               instr     Reverb 
               denorm    garvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
asig           reverb    garvb, 3.1
               outs      (asig * k2) * chnget:k("masterLvl"), ((asig * k3) * (-1)) * chnget:k("masterLvl")
garvb          =         0
               endin

</CsInstruments>
<CsScore>
f0 z
i1 0 [60*60*24*7] 
i "Reverb" 0 [60*60*24*7]  
</CsScore>
</CsoundSynthesizer>