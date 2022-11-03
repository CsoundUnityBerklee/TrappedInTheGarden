<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped04rev") size(650, 700), guiMode("queue") pluginId("def1")

button  bounds(290, 106, 86, 55) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(320, 166, 27, 31), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(288, 198, 81, 16), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9") alpha(0.99)
hslider bounds(248, 218, 175, 50) channel("reTrigRate") range(0.1, 6, 1, 0.5, 0.001) text("ReTrig Rate") textColour(255, 255, 255, 255)

hslider bounds(388, 140, 175, 50) channel("dur") range(.5, 4, 1, 1, 0.001) text("Dur") textColour("white")

hslider bounds(254, 2, 158, 50) channel("masterLvl") range(0, 1, 0.7, 1, 0.001) text("Master Lvl") textColour("white")
hslider bounds(96, 52, 158, 50) channel("synthNoiseMix") range(0, 1, 0.8, 1, 0.001) text("Syn/Nse Mix") textColour("white")
hslider bounds(254, 52, 160, 50) channel("amp") range(0, 1, 0.5, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)

hslider bounds(412, 52, 150, 50) channel("rvbLvl") range(0, 1, 0.5, 1, 0.001) text("Verb Lvl") textColour("white")
hslider bounds(98, 502, 161, 50) channel("rvbSend") range(0, 1, .15, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(270, 502, 150, 50) channel("rvbPanRate") range(.001, 9, .9, 1, 0.001) text("RvbPanRate") textColour("white")
hslider bounds(430, 502, 150, 50) channel("rvbRndRate") range(1, 3, 1, 1, 0.001) text("RvbRndRate") textColour("white")

hslider bounds(174, 282, 160, 52) channel("carFrq") range(20, 3000, 1100, 1, 0.001) text("CarFrq") textColour("white")
hslider bounds(334, 282, 159, 52) channel("carRndFrq") range(1, 4, 1, 1, 0.001) text("CarRndFrq") textColour("white")

hslider bounds(96, 340, 160, 52) channel("modFrq") range(1, 3000, 13, 1, 0.001) text("ModFrq") textColour("white")
hslider bounds(258, 340, 150, 50) channel("modRndFrq") range(1, 4, 1, 1, 0.001) text("ModRndFrq") textColour("white")
hslider bounds(434, 338, 150, 50) channel("modAmp") range(.2, 500, .6, 1, 0.001) text("ModAmp") textColour("white")

hslider bounds(112, 396, 161, 51) channel("fltSweepStart") range(40, 7000, 3000, 1, 0.001) text("FltSwpSt") textColour("white")
hslider bounds(276, 396, 161, 51) channel("fltRndStart") range(1, 2, 1, 1, 0.001) text("FltRndSt") textColour("white")
hslider bounds(112, 446, 161, 51) channel("fltSweepEnd") range(40, 7000, 1000, 1, 0.001) text("FltSwpNd") textColour("white")
hslider bounds(276, 446, 161, 51) channel("fltRndEnd") range(1, 2, 1, 1, 0.001) text("FltRndNd") textColour("white")
hslider bounds(446, 422, 151, 50) channel("fltBW") range(20, 40, 35, 1, 0.001) text("FltBW") textColour("white")

hslider bounds(56, 570, 272, 50) channel("macro1") range(.1, 3, .2, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(56, 622, 272, 50) channel("macro2") range(1, 20, 5, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(332, 570, 272, 50) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(332, 626, 272, 50) channel("macro4") range(.4, 10, 2, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(178, 136, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1") text("Noisy Down", "Bells with some Noise", "Med Bells with Noise in Mid", "RandomNoiseSweeps", "Noise Warble", "NoiseWarble2", "Noise Down", "Wacky", "Wacky2", "Bells with RandFilts")
filebutton bounds(114, 136, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(114, 164, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
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

gaRvb  init  0

giFn01 ftgen  1, 0, 8192, 10, 1
giFn15 ftgen 15, 0, 8192,  9, 1, 1, 90

maxalloc "Trapped04", 20


instr 1   
    kTrig   chnget "trigger"
    kReTrig chnget "reTrigger"
        if kReTrig == 1 then
            kRndH randh chnget:k("reTrigRate")*chnget:k("macro4") * .4, 4
            kTrig metro chnget:k("reTrigRate")*chnget:k("macro4") + kRndH
        endif

        if changed(kTrig) == 1 then
            event "i", "Trapped04", 0, chnget:i("dur") 
        endif       
endin


            instr     Trapped04

iDur        = chnget:i("dur")
iAmp        = chnget:i("amp")            
kCarFrq     = chnget:k("carFrq")*rnd(chnget:i("carRndFrq"))
kModFrq     = chnget:k("modFrq")*rnd(chnget:i("modRndFrq"))
kModAmp     = chnget:k("modAmp")*rnd(10)

iFltSwpStrt   = chnget:i("fltSweepStart")*rnd(chnget:i("fltRndStart"))
iFltSwpEnd    = chnget:i("fltSweepEnd")*rnd(chnget:i("fltRndEnd")) 
kFltBW        = chnget:k("fltBW")

kSweep         expon     iFltSwpStrt, iDur, iFltSwpEnd                    
aNoise         rand      .4                         
aFltNoise      reson     aNoise, kSweep, kSweep / kFltBW, 1  
          
aMod           oscil     kModAmp, kModFrq, 1, .1               
kEnv           expon     iAmp, iDur, .001 
aCar           oscil     kEnv, (kCarFrq + aMod) * chnget:k("macro1"), 15


;               outs      (aFltNoise * .8) + aCar, (aFltNoise * .6) + (aCar * .7)

                                                                                      
;kgate         transeg   1, iDur, 0, 0 
;amix           =        (aL + aR) * kgate

aMix         ntrpol   aCar, aFltNoise, chnget:k("synthNoiseMix")  ; synth-noise mix   

aMix         moogladder2  aMix, 200 * chnget:k("macro2"), .8

             outs      aMix * chnget:k("masterLvl") * chnget:k("macro3"), aMix * chnget:k("masterLvl") * chnget:k("macro3")
                                               
gaRvb          =         gaRvb + (aMix * chnget:k("rvbSend") * (1-chnget:k("macro3"))) 

               endin

               instr     Reverb 
               denorm    gaRvb                   
k1             oscil     .5, chnget:k("rvbPanRate")*rnd(chnget:k("rvbRndRate")), 1
k2             =         .5 + k1
k3             =         1 - k2
aSig           reverb    gaRvb, 2.5
                           outs      (aSig * k2) * chnget:k("rvbLvl") * chnget:k("masterLvl") * chnget:k("macro3"), ((aSig * k3) * (-1)) * chnget:k("rvbLvl") * chnget:k("masterLvl") * chnget:k("macro3")
gaRvb          =         0
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

