<Cabbage>
form caption("Fire") size(400, 300),  pluginID("def1")
rslider bounds(10, 8, 100, 100) channel("density"), text("Crackel Density") range(0, 16, 10, 1, 0.001)
rslider bounds(100, 8, 100, 100) channel("crackleGain"), text("Crackle Gain"), range(0, 1, 1, 1, 0.001)
rslider bounds(190, 8, 100, 100) channel("hissNoise"), text("Hiss Noise"), range(0, .22, 0.04, 1, 0.001)
rslider bounds(280, 8, 100, 100) channel("flameGain"), text("Flame Gain") range(0, 1, .1, 1, 0.001)
button bounds(12, 114, 80, 40) channel("playButton") text("Start Fire", "Stop Fire")
</Cabbage>
<CsoundSynthesizer>
<CsOptions>
-n -d -m0d
</CsOptions>
<CsInstruments>
; Initialize the global variables. 
sr = 44100
ksmps = 32
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
			event "i", "HISS", 0, -1
			event "i", "FLAMES", 0, -1
		else
			turnoff2 "CRACKLE", 1, 0
			turnoff2 "HISS", 1, 0
			turnoff2 "FLAMES", 1, 0
		endif
	endif
endin

instr CRACKLE
	a1 dust2 1, chnget:k("density")
	outs a1*chnget:k("crackleGain"), a1*chnget:k("crackleGain")
endin

instr HISS
	aNoise1 noise .8, 0
	aFlt butterhp aNoise1, 2000
	outs aFlt*chnget:k("hissNoise"), aFlt*chnget:k("hissNoise")
endin

instr FLAMES
	a1 noise 1, 0
	a2 tone a1, 100+jitter:k(10, 1, 3)
	outs a2*chnget:k("flameGain"), a2*chnget:k("flameGain")
endin

</CsInstruments>
<CsScore>
;starts instrument 1 and runs it for a week
i"CONTROLLER" 0 [60*60*24*7] 
</CsScore>
</CsoundSynthesizer>
