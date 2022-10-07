<Cabbage> bounds(0, 0, 0, 0)
form caption("Trapped12rev") size(700, 430), guiMode("queue") pluginId("def1")

button  bounds(42, 66, 101, 44) channel("trigger") text("Trigger") textColour("white")
checkbox bounds(76, 116, 27, 28), channel("reTrigger"), fontColour:0(255, 255, 255, 255)
label    bounds(34, 152, 114, 22), text("ReTrigger"), fontColour(255, 255, 255, 255) channel("label9")
hslider bounds(12, 178, 175, 50) channel("reTrigRate") range(0.02, 20, 2, 1, 0.001) text("ReTrig Rate") textColour(255, 255, 255, 255)

hslider bounds(432, 10, 175, 50) channel("dur") range(.01, 6, 2.4, 1, 0.001) text("Dur") textColour("white")

hslider bounds(266, 10, 158, 50) channel("masterLvl") range(0, 1, 0.7, 1, 0.001) text("Master Lvl") textColour("white")

hslider bounds(210, 66, 150, 50) channel("synthLvl") range(0, 1, 0.7, 1, 0.001) text("Synth Lvl") textColour(255, 255, 255, 255)
hslider bounds(366, 68, 150, 50) channel("noiseLvl") range(0, 1, 0.2, 1, 0.001) text("Noise Lvl") textColour(255, 255, 255, 255)
hslider bounds(524, 66, 150, 50) channel("verbLvl") range(0, 1, 0.5, 1, 0.001) text("Verb Lvl") textColour("white")

hslider bounds(256, 126, 160, 52) channel("frq") range(200, 4000, 1300, 1, 0.001) text("Freq") textColour("white")
hslider bounds(432, 126, 150, 50) channel("rndFrq") range(1, 4, 2, 1, 0.001) text("RandFreq") textColour("white")

hslider bounds(204, 188, 161, 51) channel("fltStrt") range(80, 8000, 1200, 1, 0.001) text("FilterStart") textColour("white")
hslider bounds(364, 186, 161, 51) channel("fltPeak") range(80, 8000, 2200, 1, 0.001) text("FilterPeak") textColour("white")
hslider bounds(524, 188, 151, 50) channel("fltBW") range(.01, .5, .07, 1, 0.001) text("FilterBW") textColour("white")

hslider bounds(256, 244, 161, 52) channel("rvbSend") range(0, 1, .15, 1, 0.001) text("Rvb Send") textColour("white")
hslider bounds(430, 246, 150, 50) channel("rvbPan") range(.001, 16, 11, 1, 0.001) text("Rvb Pan") textColour("white")

hslider bounds(82, 304, 272, 50) channel("macro1") range(.05, 8, 1, .5, 0.001) text("M1y-pitch") textColour(255, 255, 255, 255)
hslider bounds(82, 356, 272, 50) channel("macro2") range(1, 22, 8, .5, 0.001) text("M2x-filt") textColour(255, 255, 255, 255)
hslider bounds(370, 304, 272, 55) channel("macro3") range(0, 1, .8, .5, 0.001) text("M3z-volVrb") textColour(255, 255, 255, 255)
hslider bounds(370, 360, 272, 50) channel("macro4") range(.13, 10, 2, .4, 0.001) text("M4rot-Rate") textColour(255, 255, 255, 255)

combobox bounds(74, 6, 100, 25), populate("*.snaps"), channelType("string") automatable(0) channel("combo31")  value("1") text("init", "tingNoise Down", "walking noisy bass", "swirling bells", "fireworks", "pitter patter", "twitter1", "twitter2", "getting dizzy", "minding my own business", "lazer shuttering", "low with shimmering noise", "noisy old mower")
filebutton bounds(8, 6, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(8, 34, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")
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
ksmps  = 32
nchnls = 2
0dbfs  = 1
 
garvb  init  0

giFun01 ftgen 01, 0, 8192, 10, 1
giFun22 ftgen 22, 0,    8, -2, .001, .004, .007, .003, .002, .005, .009, .006

instr 1
    iDur = chnget:i("dur")
    iAmp = chnget:i("synthLvl")
    iFrq = chnget:i("frq")*rnd(chnget:i("rndFrq"))

    kTrig   chnget "trigger"
    kReTrig chnget "reTrigger"
           
    if kReTrig == 1 then
        kRndH randh chnget:k("reTrigRate")*chnget:k("macro4")*0.4, 4
        kTrig metro chnget:k("reTrigRate")*chnget:k("macro4")+kRndH
    endif

    if changed(kTrig) == 1 then
        event "i", "Trapped12", 0, iDur, iFrq, iAmp 
    endif
   
endin

               instr     Trapped12
                      
iDur           =         chnget:i("dur")
iAmp           =         chnget:i("synthLvl")             
iFrq           =         chnget:i("frq")*rnd(chnget:i("rndFrq"))

iFltStrt       =         chnget:i("fltStrt")+rnd(30)
iFltPeak       =         chnget:i("fltPeak")+rnd(100)
iFltBW         =         chnget:i("fltBW")+rnd(.1)                                                                                        
                    
ifuncl         =         8                             
                                             
k1             linseg    0, iDur * .8, 8, iDur * .2, 0     
k2             phasor    k1                         
k3             table     k2 * ifuncl, 22                    

kGate          transeg   1, iDur, 0, 0
kCut           transeg   iFltStrt, iDur * .7, 1, iFltPeak, iDur * .3, iFltStrt * .9, 6
;kCut           expseg    iFltStrt, iDur * .7, iFltPeak, iDur * .3, iFltStrt * .9    

anoise         rand      10                     
aFlt           reson     anoise * chnget:k("noiseLvl"), kCut + iFrq, kCut * iFltBW, 1
aSig           oscil     kGate * iAmp * 0.7, (iFrq + k3)  * chnget:k("macro1"), 1


aMix           =         kGate * (aSig + aFlt)

aFlt         moogladder2  aMix, 200 * chnget:k("macro2"), .8


               outs      aFlt * chnget:k("masterLvl") * chnget:k("macro3") , aFlt * chnget:k("masterLvl") * chnget:k("macro3")             
garvb          =         garvb + (aFlt * chnget:k("rvbSend") * (1-chnget:k("macro3"))) 
               endin

               instr     Reverb 
               denorm    garvb                   
k1             oscil     .5, chnget:k("rvbPan"), 1
k2             =         .5 + k1
k3             =         1 - k2
aSig           reverb    garvb, 3.1
                           outs      (aSig * k2) * chnget:k("verbLvl") * chnget:k("masterLvl") * chnget:k("macro3") , ((aSig * k3) * (-1)) * chnget:k("verbLvl") * chnget:k("masterLvl") * chnget:k("macro3") 
garvb          =         0
               endin

</CsInstruments>

<CsScore>
f0 z
i1 0 [60*60*24*7] 
i "Reverb" 0 [60*60*24*7]  
</CsScore>

</CsoundSynthesizer>