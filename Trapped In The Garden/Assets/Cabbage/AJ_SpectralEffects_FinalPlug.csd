<Cabbage> bounds(0, 0, 0, 0)

form caption("AJ Spectral Delay") size(580, 500), guiMode("queue") pluginId("def1") colour(Black)
rslider bounds(392, 72, 65, 50), channel("gain"), range(0, 1, 0.7, 1, 0.01), text("Gain"), trackerColour(255, 255, 255, 255), outlineColour(0, 0, 0, 50), textColour(255, 255, 255, 255)
rslider bounds(22, 72, 65, 50) channel("rslider10001") range(0, 10, 2, 1, 0.001) text("BufLen"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
combobox bounds(468, 68, 65, 20), text("128", "256", "512", "1024", "2048", "4096", "8192"), channel("att_table"), value(5), 



rslider bounds(318, 136, 65, 50) channel("Randrate") range(0, 10, 0, 1, 0.1) text("RandRate"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(468, 140, 65, 50) channel("DryWetMix") range(0, 1, 1, 1, 0.1) text("Mix") colour(100, 80, 80, 5), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(22, 136, 65, 50) channel("Scale") range(0, 4, 1, 1, 0.001) text("PitchShift"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(96, 136, 65, 50),  text("Speed"),     channel("Speed"),     range(0, 4, 1, 0.5, 0.01), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(96, 72, 65, 50), text("Feedback"),  channel("Feedback"),        range(0, 1.5, 0, 1, 0.001),           textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(392, 136, 65, 50), text("Blurtime"),  channel("Blurtime"),        range(0, 2, 0, 1, 0.001),           textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)

rslider bounds(170, 72, 65, 50) channel("PhOffsetL") range(0, 1, 0, 1, 0.1) text("OffsetL"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(170, 136, 65, 50) channel("PhOffsetR") range(0, 1, 0, 1, 0.1) text("OffsetR"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(244, 72, 65, 50) channel("DelayL") range(0, 5, 0, 1, 0.1) text("DelayL"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(244, 136, 65, 50) channel("DelayR") range(0, 5, 0, 1, 0.1) text("DelayR"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)



checkbox  channel("Freeze") bounds(468, 116, 66, 18) text("Freeze")

rslider bounds(318, 72, 65, 50) channel("FreezeRate") range(0, 5, 1, 1, 0.01) text("FreezeRate"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)



rslider channel("Gainb1") range(0, 1, 0, 1, 0.01) bounds(60, 220, 60, 60) text("Gain1"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider channel("Gainb2") range(0, 1, 0, 1, 0.01) bounds(172, 220, 60, 60) text("Gain2"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider channel("Gainb3") range(0, 1, 0, 1, 0.01) bounds(286, 220, 60, 60) text("Gain3"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)


rslider bounds(60, 292, 60, 60) channel("Minfreq1") range(40, 20000, 125, 0.25, 1) text("MinFreq1"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(172, 292, 60, 60) channel("Minfreq2") range(40, 20000, 1000, 0.25, 1) text("MinFreq2"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(286, 292, 60, 60) channel("Minfreq3") range(40, 20000, 4000, 0.25, 1) text("MinFreq3"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)


rslider bounds(60, 362, 60, 60) channel("Maxfreq1") range(40, 20000, 1000, 0.25, 1) text("MaxFreq1"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(172, 362, 60, 60) channel("Maxfreq2") range(40, 20000, 4000, 0.25, 1) text("MaxFreq2"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider bounds(286, 362, 60, 60) channel("Maxfreq3") range(40, 20000, 10000, 0.25, 1) text("MaxFreq3"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)


rslider  channel("Offset1") range(0, 10, 0, 1, 0.5) bounds(60, 434, 60, 60) text("Offset1"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider  channel("Offset2") range(0, 10, 0, 1, 0.5) bounds(172, 434, 60, 60) text("Offset2"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)
rslider  channel("Offset3") range(0, 10, 0, 1, 0.5) bounds(286, 434, 60, 60) text("Offset3"), textColour(255, 255, 255, 255),    colour(100, 80, 80, 5) trackerColour(192, 192, 192, 255)

checkbox bounds(468, 92, 65, 20) channel("test"), text("test"), outlineColour(0, 0, 0, 50) colour:1(255, 255, 255, 255) corners(5)

combobox bounds(394, 222, 128, 25), populate("*.snaps"), channelType("string") automatable(0) channel("preset")  value("1") 
filebutton bounds(394, 254, 60, 25), text("Save", "Save"), populate("*.snaps", "test"), mode("named preset") channel("filebutton32")
filebutton bounds(462, 254, 60, 25), text("Remove", "Remove"), populate("*.snaps", "test"), mode("remove preset") channel("filebutton33")



label  channel("label10030")  text("AJ Spectral Effects") bounds(134, 20, 319, 33)

</Cabbage> 

<CsoundSynthesizer>
<CsOptions>
-d -n
</CsOptions>
<CsInstruments> 
; Initialize the global variables. 
ksmps = 64
nchnls = 2
0dbfs = 1

gih  init 0 
gkt init 0
gkrandrate init 0 


instr 1

//FFT Attribute tables from Ian McCurdy
giFFTattributes1    ftgen    0, 0, 4, -2,  128,  64,  128, 1
giFFTattributes2    ftgen    0, 0, 4, -2,  256, 128,  256, 1
giFFTattributes3    ftgen    0, 0, 4, -2,  512, 128,  512, 1
giFFTattributes4    ftgen    0, 0, 4, -2, 1024, 256, 1024, 1
giFFTattributes5    ftgen    0, 0, 4, -2, 2048, 512, 2048, 1
giFFTattributes6    ftgen    0, 0, 4, -2, 4096,1024, 4096, 1
giFFTattributes7    ftgen    0, 0, 4, -2, 8192,2048, 8192, 1
 
ktest chnget "test"

kgain chnget "gain"
ibuflen chnget "BufferLength"
gkrandrate chnget "Randrate"
kFFTindex chnget "FFTindex"
kmix chnget "DryWetMix"
kscale chnget "Scale"
kspeed chnget "Speed" 
kfeedback chnget "Feedback"
kPhOffsetL chnget "PhOffsetL" // 0-1
kPhOffsetR chnget "PhOffsetR"
ktrig chnget "Freeze"
kfreezerate chnget "FreezeRate"
kdelayL chnget "DelayL"
kdelayR chnget "DelayR"
kmin1 chnget "Minfreq1"
kmax1 chnget "Maxfreq1"
kmin2 chnget "Minfreq2"
kmax2 chnget "Maxfreq2"
kmin3 chnget "Minfreq3"
kmax3 chnget "Maxfreq3"
kpreset chnget "Preset"
kblurtime chnget "Blurtime"

  katt_table    init    5
katt_table    chnget    "att_table"    ; FFT atribute table
  
    

 
ibuflen init 4
aFB init 0
kPhOffsetL init 0 
kPhOffsetR init 0 



alive1, alive2 ins 
alive = alive1 + alive2

ain = alive*0.5

iFFTsize chnget "FFt1"
ioverlap = iFFTsize/4
iwinsize = iFFTsize
iwintype = 1

if changed(katt_table, iFFTsize, kpreset)==1 then    
  reinit    RESTART                                                   
 endif
 RESTART:    

 iFFTsize    table    0, giFFTattributes1 + i(katt_table) - 1
 ioverlap    table    1, giFFTattributes1 + i(katt_table) - 1 // FFT attribute tables from McCurdy Examples
 iwinsize    table    2, giFFTattributes1 + i(katt_table) - 1
 iwintype    table    3, giFFTattributes1 + i(katt_table) - 1

fsig pvsanal    ain + aFB, iFFTsize, ioverlap, iwinsize, iwintype 
gih, gkt pvsbuffer fsig, ibuflen
kh init gih 


kgate lfo 1, kfreezerate, 3
iphasor        ftgen        0, 0, 65536, 7, 0, 65536, 1 // Phasor pointer from  Mccurdy

	
	         
    
    areadL         osciliktp     kspeed/ibuflen, iphasor, kPhOffsetL        
    kreadL        downsamp    areadL
    kreadL        =        kreadL * ibuflen
    
    kfzL samphold kreadL, kgate
    
    if (ktrig == 1)  then 
    kpointL = kfzL
    elseif (ktrig == 0) then
    kpointL = kreadL
    endif
    
    fbufL pvsbufread kpointL - kdelayL, kh  
    fscaleL pvscale fbufL, kscale 
    fblurL pvsblur fscaleL, kblurtime, 1
    aresynL pvsynth fblurL
   
	
    
    areadR         osciliktp     kspeed/ibuflen, iphasor, kPhOffsetR        
    kreadR        downsamp    areadR
    kreadR        =        kreadR * ibuflen
    
    kfzR samphold kreadR, kgate
    
    if (ktrig == 1)  then 
    kpointR = kfzR
    elseif (ktrig == 0) then
    kpointR = kreadR
    endif
    
    fbufR pvsbufread kpointR - kdelayR, kh  
    fscaleR pvscale fbufR, kscale 
    fblurR pvsblur fscaleR, kblurtime, 1
    aresynR pvsynth fblurR


	aFBL dcblock2 aresynL * kfeedback
	aFBR dcblock2 aresynR * kfeedback

    aFB = aFBL + aFBR
	
	amixL ntrpol ain, aresynL, kmix
	amixR ntrpol ain, aresynR, kmix
	
	outs amixL, amixR
	
if changed(kmin1, kmax1, kmin2, kmax2, kmin3, kmax3)==1 then    
  reinit    UPDATE                                                   
 endif
 UPDATE:  
	

kgainb1 chnget "Gainb1"
idelay1 chnget "Offset1"
idelay1 init 0
kranddelay randi 2.0, gkrandrate, 0.5, 0, idelay1
fband1 pvsbufread gkt*kranddelay+(idelay1*1000), kh, i(kmin1), i(kmax1)
aband1 pvsynth fband1



kgainb2 chnget "Gainb2"
idelay2 chnget "Offset2"
idelay2 init 0
kranddelay randi 2.0, gkrandrate, 0.5, 0, idelay2
fband2 pvsbufread gkt*kranddelay+(idelay2*1000), kh, i(kmin2), i(kmax2)
aband2 pvsynth fband2


kgainb3 chnget "Gainb3"
idelay3 chnget "Offset3"
idelay3 init 0
kranddelay randi 2.0, gkrandrate, 0.5, 0, idelay3
fband3 pvsbufread gkt*kranddelay+(idelay3*1000), kh, i(kmin3), i(kmax3)
aband3 pvsynth fband3


aoutl sum aband1*kgainb1*0.5, aband2*kgainb2*0.5, aband3*kgainb3*0.5
aoutr sum aband1*kgainb1*0.5, aband2*kgainb2*0.5, aband3*kgainb3*0.5

aclipl clip aoutl, 0, 0.9
aclipr clip aoutr, 0, 0.9

outs aclipl, aclipr

endin 

</CsInstruments>
<CsScore>
;starts instrument 1 and runs it for a week
i1 0 [60*60*24*7] 

</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>0</y>
 <width>0</width>
 <height>0</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
