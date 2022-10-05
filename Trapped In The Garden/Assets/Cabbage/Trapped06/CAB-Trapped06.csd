<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped06rev") size(600, 600), guiMode("queue") pluginId("def1")

button  bounds(62, 14, 86, 55) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(94, 72, 27, 31), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(40, 106, 132, 20), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9") alpha(0.99)
hslider bounds(24, 130, 175, 50) channel("reTrigRate") range(0.1, 6, 1, 0.5, 0.001) text("ReTrig Rate") textColour(255, 255, 255, 255)

hslider bounds(202, 56, 175, 50) channel("dur") range(1, 9, 4, 1, 0.001) text("Dur") textColour("white")
hslider bounds(304, 112, 158, 50) channel("masterLvl") range(0, 1, 0.8, 1, 0.001) text("Master Lvl") textColour("white")
hslider bounds(390, 166, 162, 50) channel("verbLvl") range(0, 1, 0.4, 1, 0.001) text("Verb Lvl") textColour("white")
hslider bounds(210, 166, 175, 50) channel("amp") range(0, 1, 0.7, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)
hslider bounds(138, 332, 160, 52) channel("strtFrq") range(20, 3000, 400, 1, 0.001) text("FltSweepSt") textColour("white")
hslider bounds(300, 332, 150, 50) channel("endFrq") range(22, 4000, 1200, 1, 0.001) text("FltSweepNd") textColour("white")
hslider bounds(200, 276, 150, 50) channel("rndFrq") range(0, 1000, 300, 1, 0.001) text("FltRndStNd") textColour("white")
hslider bounds(358, 274, 151, 50) channel("bw") range(.001, .1, .03, 1, 0.001) text("FltBW") textColour("white")
hslider bounds(216, 388, 151, 48) channel("rate") range(.6, 17, 10, 1, 0.001) text("Rate") textColour("white")
hslider bounds(110, 222, 177, 50) channel("rvbSend") range(0, 1, 0.8, 1, 0.001) text("Rvb Send") textColour(255, 255, 255, 255)
hslider bounds(294, 220, 160, 50) channel("rvbPan") range(.01, 9, 4, 1, 0.001) text("Rvb Pan") textColour("white")

hslider bounds(26, 444, 272, 50) channel("macro1") range(.1, 3, .2, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(26, 496, 272, 50) channel("macro2") range(1, 20, 5, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(310, 442, 272, 50) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(310, 498, 272, 50) channel("macro4") range(.4, 10, 2, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(454, 56, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1")
filebutton bounds(390, 56, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(390, 84, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
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
giFn19 ftgen 19, 0,   8,  2, 1, 7, 10, 7, 6, 5, 4, 2

instr 1
    iDur = chnget:i("dur")

    kTrig chnget "trigger"
    kReTrig chnget "reTrigger"

        if kReTrig == 1 then
            kRndH randh chnget:k("reTrigRate")*chnget:k("macro4") * .4, 4
            kTrig metro chnget:k("reTrigRate")*chnget:k("macro4") + kRndH
        endif

        if changed(kTrig) == 1 then
            event "i", "Trapped06", 0, iDur
        endif
endin

            instr     Trapped06

iFnLen      = 8  

iDur        = chnget:i("dur")

iAmp        = chnget:i("amp")
              
iStFltFrq   = chnget:i("strtFrq")+rnd(chnget:i("rndFrq"))
iEndFltFrq  = chnget:i("endFrq")+rnd(chnget:i("rndFrq"))

kRate       = chnget:k("rate")  

kBW         = chnget:k("bw")
                                                                                                                                                       
kPhase     phasor    kRate                          
k2         table     kPhase * iFnLen, 19                      
aNoise     rand      .4                        
k3         expon     iStFltFrq, iDur, iEndFltFrq                       
aSig       butterbp  aNoise, k3 * k2 * chnget:k("macro1"), k3 * kBW, 1

aFlt         moogladder2  aSig, 200 * chnget:k("macro2"), .8

               outs      aFlt * chnget:k("masterLvl") * chnget:k("macro3"), aFlt * chnget:k("masterLvl") * chnget:k("macro3")            
gaRvb          =         gaRvb + (aFlt * chnget:k("rvbSend") * (1-chnget:k("macro3"))) 
               endin


   instr     Reverb 
               denorm    gaRvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
aSig           reverb    gaRvb, 2.1
               outs      (aSig * k2) * chnget:k("verbLvl") * chnget:k("masterLvl") * chnget:k("macro3"), ((aSig * k3) * (-1)) * chnget:k("verbLvl") * chnget:k("masterLvl") * chnget:k("macro3")
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