<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped09rev") size(650, 450), guiMode("queue") pluginId("def1")

button  bounds(70, 72, 101, 44) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(104, 122, 27, 28), channel("reTrigger"), , fontColour:0(255, 255, 255, 255)
label    bounds(64, 152, 114, 22), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9")
hslider bounds(38, 176, 175, 50) channel("reTrigRate") range(.02, 20, 2, 1, 0.001) text("ReTrig Rate") textColour("white")

hslider bounds(330, 52, 150, 50) channel("dur") range(2, 9, 4, 1, 0.001) text("Dur") textColour("white")
hslider bounds(240, 110, 150, 50) channel("note") range(20, 80, 50, 1, 0.001) text("MIDI NN") textColour("white")
hslider bounds(398, 110, 150, 50) channel("rndNote") range(0, 8, 3, 1, 0.001) text("Rnd NN") textColour("white")

hslider bounds(482, 52, 150, 50) channel("amp") range(0, 1, .6, 1, 0.001) text("Synth Lvl") textColour("white")

hslider bounds(276, 164, 162, 50) channel("rndRate") range(100, 400, 185, 1, 0.001) text("RndRate") textColour("white")
hslider bounds(442, 164, 150, 50) channel("rndAmp") range(0, 10, 3.3, 1, 0.001) text("RndAmp") textColour("white")

hslider bounds(336, 236, 150, 50) channel("delaySend") range(0, 1, .76, 1, 0.001) text("Delay Send") textColour("white")
hslider bounds(488, 236, 150, 50) channel("delayTime") range(.001, 5, .08, 1, 0.001) text("Delay Time") textColour("white")

hslider bounds(20, 238, 150, 50) channel("rvbSend") range(0, 1, .45, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(174, 238, 150, 50) channel("rvbPan") range(0, 6, 4, 1, 0.001) text("Rvb Pan") textColour("white")

hslider bounds(178, 52, 150, 50) channel("masterLvl") range(0, 1, 0.9, 1, 0.001) text("Master Lvl") textColour("white")

hslider bounds(46, 302, 272, 50) channel("macro1") range(1, 40, 1, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(46, 354, 272, 50) channel("macro2") range(1, 20, 5, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(330, 300, 272, 50) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(330, 356, 272, 50) channel("macro4") range(.2, 10, 2, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(78, 12, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31") text("Low Pad1", "Lower - Breathing", "Lower", "Higher + Rough", "Low Pad2", "Medium Pad") value("1")
filebutton bounds(16, 12, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(16, 42, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
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
; Initialize the global variables. 
ksmps = 32
nchnls = 2
0dbfs = 1

garvb          init      0
gadel          init      0

giSine ftgen 1, 0, 8192, 10, 1
giWav2 ftgen 2, 0, 8192, 10, 10, 8, 0, 6, 0, 4, 0, 1
giWav3 ftgen 3, 0, 8192, 10, 10, 0, 5, 5, 0, 4, 3, 0, 1
giWav4 ftgen 4, 0, 8192, 10, 10, 0, 9, 0, 0, 8, 0, 7, 0, 4, 0, 2, 0, 1

gkRevPan init 4

instr 1
    iDur = chnget:i("dur")
 
    iNote = chnget:i("frq")+rnd(chnget:i("rndNote"))
    iFrq = cpsmidinn(iNote)
    iAmp = chnget:i("amp")
    
    kTrig chnget "trigger"
    kReTrig chnget "reTrigger"

    if kReTrig == 1 then
        kRndH randh chnget:k("reTrigRate")*chnget:k("macro4")*0.4, 4
        kTrig metro chnget:k("reTrigRate")*chnget:k("macro4")+kRndH
        iDur = .65
    endif
    
    if changed(kTrig) == 1 then
        event "i", "Trapped09", 0, iDur, iFrq, iAmp
    endif
endin


instr     Trapped09

ip3    = chnget:i("dur")

iamp   = chnget:i("amp")*.2
              
kNote  = chnget:k("note")+rnd(chnget:i("rndNote"))
kFrq   = cpsmidinn(kNote)*.25

kRndAmp  = chnget:k("rndAmp")
kRndFrq  = chnget:k("rndRate")
                                                                                        
k2             randh     kRndAmp, kRndFrq, .1                     
k3             randh     kRndAmp * .98, kRndFrq * .91, .2             
k4             randh     kRndAmp * 1.2, kRndFrq * .96, .3            
k5             randh     kRndAmp * .9, kRndFrq * 1.3     
                       
kenv           linen    iamp, ip3 *.2, ip3, ip3 * .8  

a1             oscil     kenv, (kFrq + k2) * chnget:k("macro1"), giSine, .2             
a2             oscil     kenv * .91, ((kFrq + .004) + k3) * chnget:k("macro1"), giWav2, .3
a3             oscil     kenv * .85, ((kFrq + .006) + k4) * chnget:k("macro1"), giWav3, .5
a4             oscil     kenv * .95, ((kFrq + .009) + k5) * chnget:k("macro1"), giWav4, .8

kgate         transeg   1, ip3, 0, 0 
amix           =        (a1 + a2 + a3 + a4) * kgate
aL             =        a1 + a3
aR             =        a2 + a4

aFltL         moogladder2  aL, 200 * chnget:k("macro2"), .8
aFltR         moogladder2  aL, 200 * chnget:k("macro2"), .8

kgate         transeg   1, ip3, 0, 0 
aMix           =        (aFltL + aFltR) * kgate

              outs      aFltL * chnget:k("masterLvl") * chnget:k("macro3"), aFltR * chnget:k("masterLvl") * chnget:k("macro3")
                
garvb          =         garvb + (aMix * chnget:k("rvbSend") * (1-chnget:k("macro3"))) 
gadel          =         gadel + (aMix * chnget:k("delaySend") * (1-chnget:k("macro3"))) 
               
endin

               instr     Delay
               denorm    gadel
ip3    = chnget:i("dur")
kgate          expseg    1, ip3*.7, 1, ip3*.3, .0001
asig           delay     gadel, chnget:i("delayTime")
asig = asig*kgate
kgate adsr .01,.01,.9,.1
               outs      asig*chnget:k("masterLvl") * kgate  * chnget:k("macro3"), asig*chnget:k("masterLvl") * kgate  * chnget:k("macro3")
gadel          =         0
               endin


               instr     Reverb 
               denorm    garvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
asig           reverb    garvb, 3.1
kgate adsr .01,.01,.9,.1
               outs      (asig * k2) * chnget:k("masterLvl") * kgate  * chnget:k("macro3"), ((asig * k3) * (-1)) * chnget:k("masterLvl") * kgate  * chnget:k("macro3")
garvb          =         0
               endin

</CsInstruments>
<CsScore>
;causes Csound to run for about 7000 years...
f0 z
;starts instrument 1 and runs it for a week
i1 0 [60*60*24*7] 
i "Delay" 0 [60*60*24*7]
i "Reverb" 0 [60*60*24*7]  
</CsScore>
</CsoundSynthesizer>