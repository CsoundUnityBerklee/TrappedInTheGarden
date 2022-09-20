<Cabbage>
form caption("Fire II") size(400, 300),  pluginID("def1")
rslider bounds(10, 8, 100, 100) channel("density"), text("Crackle Density") range(1,80, 16, 1, 0.001)
rslider bounds(100, 8, 100, 100) channel("crackleGain"), text("Crackle Gain"), range(0, 1, 1, 1, 0.001)
rslider bounds(190, 8, 100, 100) channel("hissNoise"), text("Hiss Noise"), range(0, 1, 0.8, 1, 0.001)
rslider bounds(280, 8, 100, 100) channel("flameGain"), text("Flame Gain") range(0, 1, .06, 1, 0.001)
button bounds(12, 114, 90, 40) channel("playButton") text("Start Fire", "Stop Fire")
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
-n -d -m0d
</CsOptions>
<CsInstruments>
; Initialize the global variables. 
sr = 44100
ksmps = 16
nchnls = 2
0dbfs = 1

; Rory Walsh 2017, based something Eric 
; Grehan showed me in class. I basically 
; swapped his use of the noise opcode 
; for the dust2 opcode, which I think 
; gives a better crackle. 

instr CONTROLLER
	kPlayButton chnget "playButton"
	if changed(kPlayButton) == 1 then
		if kPlayButton == 1 then
			event "i", "CRACKLE", 0, -1
			event "i", "HISS", 0, 3600
			event "i", "HISS", 0, 3600
			event "i", "FLAMES", 0, 3600
			event "i", "FLAMES", 0, 3600
		else
			turnoff2 "CRACKLE", 1, 0
			turnoff2 "HISS", 0, 0
			turnoff2 "FLAMES", 0, 0
		endif
	endif
endin

instr CRACKLE
	a1 gausstrig 1,chnget:k("density"),30
	kCF	randomh	8.5,14,chnget:k("density")
	a1	reson	a1,cpsoct(kCF),cpsoct(kCF),1
	a1	*=		randomh:k(0.2,1,chnget:k("density"))
	aL,aR	pan2	a1,randomh:k(0.1,0.9,chnget:k("density"))
	outs aL*chnget:k("crackleGain"), aR*chnget:k("crackleGain")
endin

instr HISS
    kdB	randomh	-6,0,10
	aNoise1 dust2 .05*port(ampdbfs(kdB),0.1), randomi:k(4000,8000,0.6)
	aFlt butterhp aNoise1, 4000
	aFlt tone aFlt, 8000
	aL,aR	pan2	aFlt,jspline(0.4,1,1)+0.5
	outs aL*chnget:k("hissNoise"), aR*chnget:k("hissNoise")
endin

instr FLAMES
	a1 noise 1, 0
	a1 butbp a1, 30, 30/5
	a1 buthp a1*100, 25
	a1 clip a1, 1, .3
	a1 buthp a1, 25
	aL,aR	pan2	a1,jspline(0.4,1,3)+0.5
	outs aL*chnget:k("flameGain"), aR*chnget:k("flameGain")
endin

</CsInstruments>
<CsScore>
;starts instrument 1 and runs it for a week
i"CONTROLLER" 0 [60*60*24*7] 
</CsScore>
</CsoundSynthesizer>
