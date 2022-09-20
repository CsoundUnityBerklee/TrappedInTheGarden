<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped02") size(650, 400), guiMode("queue") pluginId("def1")

button  bounds(192, 8, 86, 55) channel("trigger") text("Trigger") textColour("white")

hslider bounds(296, 10, 158, 50) channel("masterLvl") range(0, 1, 0.7, 1, 0.001) text("Master Lvl") textColour("white")

hslider bounds(462, 8, 175, 50) channel("dur") range(2, 9, 3, 1, 0.001) text("Dur") textColour("white")
hslider bounds(62, 70, 150, 50) channel("amp") range(0, 1, 0.5, 1, 0.001) text("Amp") textColour(255, 255, 255, 255)

hslider bounds(226, 70, 159, 52) channel("note") range(10, 100, 60, 1, 0.001) text("Note") textColour("white")
hslider bounds(404, 70, 150, 50) channel("rndNote") range(-4, 4, 0, 1, 0.001) text("RandNote") textColour("white")

hslider bounds(28, 134, 151, 48) channel("shakeRate") range(0, 15, 6, 1, 0.001) text("Shaker") textColour("white")

hslider bounds(270, 130, 159, 50) channel("numHarmonics") range(5, 15, 10, 1, 0.001) text("Harmonics") textColour("white")

hslider bounds(438, 130, 150, 50) channel("sweepRate") range(.015, .75, .3, 1, 0.001) text("SweepRate") textColour("white")

hslider bounds(102, 188, 161, 50) channel("rvbSend") range(.2, 1, .23, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(360, 184, 150, 50) channel("rvbPan") range(.001, 9, .9, 1, 0.001) text("Rvb Pan") textColour("white")

hslider bounds(22, 244, 272, 50) channel("macro1") range(.1, 3, .2, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(20, 300, 272, 50) channel("macro2") range(1, 20, 5, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(320, 242, 272, 50) channel("macro3") range(.3, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(316, 296, 272, 50) channel("macro4") range(.1, 10, .1, 10, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(82, 8, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1")
filebutton bounds(18, 8, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(18, 36, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")

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

giSine  ftgen  1, 0, 8192, 10, 1
giFun15 ftgen 15, 0, 8192,  9, 1, 1, 90

;gkRevPan init 4

instr 1
    iDur = chnget:i("dur")
 
    iNote = chnget:i("note")*rnd(chnget:i("rndNote"))
    iAmp = chnget:i("amp")
    kTrig chnget "trigger"
    if changed(kTrig) == 1 then
        event "i", "Trapped02", 0, iDur, cpsmidinn(iNote), iAmp 
    endif
endin


instr Trapped02

iDur  = chnget:i("dur")
iAmp  = chnget:i("amp")             
iNote = chnget:i("note")+rnd(chnget:i("rndNote"))
iNumHarmonics = chnget:i("numHarmonics")
iSweepRate    = chnget:i("sweepRate")
ip10            midic7    25, .75, .15        ; CONTROLLER 25 = ARPEGGIO SPEED

kShakeRate = chnget:k("shakeRate")
                                                          
k1             randi     1, 30                              
k2             linseg    0, iDur * .5, 1, iDur * .5, 0     
k3             linseg    .005, iDur * .71, .015, iDur * .29, .01
k4             oscil     k2, kShakeRate, 1, .2               
k5             =         k4 + 2

ksweep         linseg    iNumHarmonics, iDur * iSweepRate, 1, iDur * (iDur - (iDur * iSweepRate)), 1

kenv           expseg    .001, iDur * .01, iAmp, iDur * .99, .001
aSig           gbuzz     kenv, (cpsmidinn(iNote) * chnget:k("macro1")) + k3, k5 * chnget:k("macro2") , ksweep, k1, 15

kgate         transeg   1, iDur, 0, 0 

aFlt         moogladder2  aSig, 200 * chnget:k("macro2"), .8

aMix           =        aFlt * kgate

             outs      aMix * (chnget:k("masterLvl")*chnget:k("macro3")), aMix * (chnget:k("masterLvl")*chnget:k("macro3"))
;             outs      aSig * chnget:k("masterLvl"), aSig * chnget:k("masterLvl")
             
garvb          =         garvb + aMix * (chnget:k("rvbSend"))*(1-chnget:k("macro3")) 
 
 
               endin

               instr     Reverb 
               denorm    garvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
asig           reverb    garvb, 3.1
               outs      (asig * k2) * (chnget:k("masterLvl")*chnget:k("macro3")), ((asig * k3) * (-1)) * (chnget:k("masterLvl")*chnget:k("macro3"))
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
