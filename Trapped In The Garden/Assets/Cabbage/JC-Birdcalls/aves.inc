/* Aves Collection version 1.0:
	a collection of bird calls for Csound, based on bird.scm from the SND
	package, which was based on bird.clm by
	bil@ccrma.Stanford.edu
	This is transcribed and tweaked by Jeanette C.
	jeanette@juliencoder.de .
*/

#ifndef M_AVES_INC_
#define M_AVES_INC_ #1#

; To find the actual UDOs to creating the bird calls, search for the all
; capital letters mark JBS

; Global ftables used throughout the m_aves library
; Sine wave
giSine = ftgen(0, 0, 32768, 10, 1)
; Table for harmonic number for additive synthesis, integers from 1
giHarmonics = ftgen(0, 0, 128, -7, 1, 128, 129)

; Generic envelope shapes
giAvesRampUp = ftgen(0, 0, 4096, 7, 0, 4096, 1)
giAvesRampDown = ftgen(0, 0, 4096, 7, 1, 4096, 0)
giAvesMainAmp = ftgen(0, 0, 4096, 7, 0, 1024, 1, 1434, .75, 614, 1.0, 1024, 0)
giAvesTap = ftgen(0, 0, 4096, 7, 0, 41, 1, 4014, 1, 41, 0)
giAvesAmp = ftgen(0, 0, 4096, 7, 0, 1024, 1, 2048, 1, 1024, 0)

/*
	_Aves_oscbank - create a bird sound based on additive synthesis and output
	it to a supplied channel. This is an auxiliary instrument to the m_aves
	library, internally used by the UDOs
	parameters:
	p4 = Schannel, p5 = iFreq, p6 = iFMScale, p7 = iAmpScale, p8 = iFreqEnvFt, 
	p9 = iAmpEnvFt, p10 = iPartialsFt
*/
instr +_Aves_oscbank
	; Initialise internal variables from parameters
	SchannelName = strget(p4)
	iFreq init p5 * (1 - rnd31(.01, 0))
	iFMScale init p6 * (1 - rnd31(.04, 0))
	iAmpScale init p7 * (1 - rnd31(.03, 0))
	iFreqEnvFt init p8
	iAmpEnvFt init p9
	iPartialsFt init p10
	iPartialCount = tableng(iPartialsFt)
	iDuration init p3
	iRandomRead init (1 - linrand(.02))

	; Create a reading pointer into the envelope ftables
	kReader = line(0, (iDuration * iRandomRead), 1)

	; Create the frequency and amplitude envelope
	kFreqEnv = table(kReader, iFreqEnvFt, 1, 0, 0)
	kFreqEnv *= iFMScale
	kAmpEnv = table(kReader, iAmpEnvFt, 1, 0, 0)
	kAmpEnv *= iAmpScale

	; Create the audio output from the additive oscillator bank
	aOsc = adsynt(kAmpEnv, (iFreq + kFreqEnv), giSine, giHarmonics, iPartialsFt, iPartialCount)
	
	; Output the audio
	chnmix(aOsc, SchannelName)
endin

/*
	_Aves_osc - Create a bird sound based on a single sine wave and output
	to the supplied channel. This is an auxiliary instrument used by the UDOs
	for the m_aves library.
	Parameters:
	p4 = Schannel, p5 = iFreq, p6 = iFMScale, p7 = iAmpScale, p8 = iFreqEnvFt,
	p9 = iAmpEnvFt
*/
instr +_Aves_osc
	; Initialise internal variables from parameters
	SchannelName = strget(p4)
	iFreq init p5 * (1 - rnd31(.01, 0))
	iFMScale init p6 * (1 - rnd31(.04, 0))
	iAmpScale init p7 * (1 - rnd31(.02, 0))
	iFreqEnvFt init p8
	iAmpEnvFt init p9
	iDuration init p3
	iRandRead = (1 - linrand(.01))

	; Create a reading pointer into the envelope ftables
	kReader = line(0, (iDuration * iRandRead), 1)

	; Create and scale the frequency and amplitude envelopes
	kFreqEnv = table(kReader, iFreqEnvFt, 1, 0, 0)
	kFreqEnv *= iFMScale
	kAmpEnv = table(kReader, iAmpEnvFt, 1, 0, 0)
	kAmpEnv *= iAmpScale

	; Create the audio with a simple sine oscillator
	aOsc = oscil(kAmpEnv, (iFreq + kFreqEnv), giSine)

	; Output the audio
	chnmix(aOsc, SchannelName)
endin

;---------------------------------------
; JBS Here are the actual UDOs to generate bird calls

; Cassins kingbird (Tyrannus vociferans)
; https://en.wikipedia.org/wiki/Cassin%27s_kingbird
; Habitat: rangeland and savanna
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - optional trigger for the bird, if omitted the bird call will be
; triggered once
opcode m_aves_cassins_kingbird, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; Cassins kingbird specific envelopes
	iCassinsFirst = ftgenonce(0, 0, -1000, 7, .3, 450, 1, 450, .1, 100, 0)
	iCassinsSecond = ftgenonce(0, 0, -1000, 7, 0, 20, .5, 20, 0, 20, .55, 20, .05, 20, \
		.6, 20, .05, 20, .65, 20, .1, 20, .7, 20, \
		.1, 20, .75, 20, .15, 20, .8, 20, .2, 20, \
		.85, 20, .25, 20, .9, 20, .3, 20, .95, 20, \
		.4, 20, 1, 20, .5, 20, 1, 20, .45, 20, \
		1, 20, .5, 20, 1, 20, .4, 20, .95, 20, \
		.4, 20, .9, 20, .4, 20, .85, 20, .35, 20, \
		.8, 20, .3, 20, .75, 20, .25, 20, .7, 20, \
		.2, 20, .65, 20, .1, 20, .6, 20, 0, 20, \
		.55, 20, 0, 20, .5, 20, 0, 20, .4)
	
	; Create partial harmonic amp ftables
	iCassinsHarmFirst = ftgenonce(0, 0, 4, 2, 1, .5, 0, .2)
	iCassinsHarmSecond = ftgenonce(0, 0, 4, 2, 1, .01, 0, .1)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_cassins_kingbird-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.04 * iDurRand), SchannelName, (1700 * iFreqScale), (1200 * iFreqScale), .15, iCassinsFirst, giAvesMainAmp, iCassinsHarmFirst)
		schedulek("_Aves_oscbank", (.09 * iDurRand), (.18 * iDurRand), SchannelName, (1700 * iFreqScale), (900 * iFreqScale), .25, iCassinsSecond, giAvesMainAmp, iCassinsHarmSecond)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Orchard oriole (Icterus spurius)
; https://en.wikipedia.org/wiki/Orchard_oriole
; Habitat: semi-open land with deciduous trees
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_orchard_oriole, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iOrioleUpDownA = ftgenonce(0, 0, -1000, 7, 0, 600, 1, 400, .6)
	iOrioleUpDownB = ftgenonce(0, 0, -1000, 7, .5, 300, 1, 700, 0)
	iOrioleEnv1 = ftgenonce(0, 0, -1000, 7, .9, 150, 1, 250, .3, 200, .6, 250, 0, 150, 0)
	iOrioleEnv2 = ftgenonce(0, 0, -1000, 7, .3, 250, 0, 750, 1)
	iOrioleMid = ftgenonce(0, 0, -1000, 7, 1, 50, .5, 50, 1, 150, 0, 600, .5, 150, 0)
	iOrioleAmp = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 900, 0)

	; Create harmonic spectra
	iOrioleHarm1 = ftgenonce(0, 0, 4, 2, 1, .02, .05, 0)
	iOrioleHarm2 = ftgenonce(0, 0, 2, 2, 1, .05)
	iOrioleHarm3 = ftgenonce(0, 0, 2, 2, 1, .04)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_orchard_oriole-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.03 * iDurRand), SchannelName, (3700 * iFreqScale), (100 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.03 * iDurRand), (.05 * iDurRand), SchannelName, (2500 * iFreqScale), (1000 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_oscbank", (.12 * iDurRand), (.1 * iDurRand), SchannelName, (2000 * iFreqScale), (800 * iFreqScale), .2, iOrioleUpDownA, giAvesMainAmp, iOrioleHarm1)
		schedulek("_Aves_osc", (.27 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (1200 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_oscbank", (.32 * iDurRand), (.21 * iDurRand), SchannelName, (2000 * iFreqScale), (1200 * iFreqScale), .15, iOrioleEnv1, giAvesMainAmp, iOrioleHarm2)
		schedulek("_Aves_osc", (.62 * iDurRand), (.05 * iDurRand), SchannelName, (4200 * iFreqScale), (1000 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_oscbank", (.72 * iDurRand), (.1 * iDurRand), SchannelName, (2000 * iFreqScale), (1000 * iFreqScale), .25, iOrioleMid, giAvesMainAmp, iOrioleHarm2)
		schedulek("_Aves_oscbank", (.92 * iDurRand), (.1 * iDurRand), SchannelName, (2000 * iFreqScale), (1000 * iFreqScale), .25, iOrioleMid, giAvesMainAmp, iOrioleHarm2)
		schedulek("_Aves_osc", (1.1 * iDurRand), (.1 * iDurRand), SchannelName, (2300 * iFreqScale), (3200 * iFreqScale), .1, iOrioleUpDownB, iOrioleAmp)
		schedulek("_Aves_osc", (1.27 * iDurRand), (.03 * iDurRand), SchannelName, (1800 * iFreqScale), (300 * iFreqScale), .05, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.32 * iDurRand), (.03 * iDurRand), SchannelName, (2200 * iFreqScale), (100 * iFreqScale), .04, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.42 * iDurRand), (.07 * iDurRand), SchannelName, (2500 * iFreqScale), (22000 * iFreqScale), .15, iOrioleUpDownB, iOrioleAmp)
		schedulek("_Aves_oscbank", (1.54 * iDurRand), (.2 * iDurRand), SchannelName, (2400 * iFreqScale), (1200 * iFreqScale), .25, iOrioleEnv2, giAvesMainAmp, iOrioleHarm2)
		schedulek("_Aves_osc", (1.82 * iDurRand), (.02 * iDurRand), SchannelName, (2200 * iFreqScale), (3000 * iFreqScale), .04, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.9 * iDurRand), (.02 * iDurRand), SchannelName, (2200 * iFreqScale), (3000 * iFreqScale), .04, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_oscbank", (2.02 * iDurRand), (.17 * iDurRand), SchannelName, (2000 * iFreqScale), (1000 * iFreqScale), .2, iOrioleUpDownA, iOrioleAmp, iOrioleHarm3)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Chipping sparrow (Spizella passerina)
; https://en.wikipedia.org/wiki/Chipping_sparrow
; Habitat: mountains, dry land
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_chipping_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iChippingUp = ftgenonce(0, 0, -1000, 7, .8, 150, 1, 600, .3, 250, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_chipping_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.06 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.12 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.18 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.24 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.3 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.36 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.42 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.48 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.54 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.6 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.66 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.72 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.78 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.84 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.9 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.96 * iDurRand), (.05 * iDurRand), SchannelName, (4000 * iFreqScale), (2400 * iFreqScale), .2, iChippingUp, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Bobwhite (Colinus virginianus - or other subspecies)
; https://en.wikipedia.org/wiki/Colinus
; Habitat: grassland, open woodland, roadsides, wood edges
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_bobwhite, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBobwhiteUp1 = ftgenonce(0, 0, -1000, 7, 0, 400, 1, 600, 1)
	iBobwhiteUp2 = ftgenonce(0, 0, -1000, 7, 0, 650, .5, 350, 1)
	
	; Create partial harmonic amp ftables
	iBobwhiteHarm = ftgenonce(0, 0, 2, 2, 1, .02)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_bobwhite-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.2 * iDurRand), SchannelName, (1800 * iFreqScale), (200 * iFreqScale), .1, iBobwhiteUp1, giAvesMainAmp, iBobwhiteHarm)
		schedulek("_Aves_oscbank", (.6 * iDurRand), (.2 * iDurRand), SchannelName, (1800 * iFreqScale), (1200 * iFreqScale), .2, iBobwhiteUp2, giAvesMainAmp, iBobwhiteHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Western meadowlark (Sturnella neglecta)
; https://en.wikipedia.org/wiki/Western_meadowlark
; Habitat: grasslands, prairies, pastures, abandoned fields
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_meadowlark, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iMeadowlarkDown = ftgenonce(0, 0, -1000, 7, 1, 400, .4, 600, 0)
	iMeadowlarkLine = ftgenonce(0, 0, 2, 2, 0, 0)
	
	; Create partial harmonic amp ftables
	iMeadowlarkHarm = ftgenonce(0, 0, 2, 2, 1, .04)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_meadowlark-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.1 * iDurRand), SchannelName, (2010 * iFreqScale), (0 * iFreqScale), .1, iMeadowlarkLine, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (.3 * iDurRand), (.15 * iDurRand), SchannelName, (3000 * iFreqScale), (100 * iFreqScale), .11, iMeadowlarkDown, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (.5 * iDurRand), (.25 * iDurRand), SchannelName, (2000 * iFreqScale), (150 * iFreqScale), .2, iMeadowlarkDown, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (.85 * iDurRand), (.15 * iDurRand), SchannelName, (3010 * iFreqScale), (250 * iFreqScale), .11, iMeadowlarkDown, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (1.05 * iDurRand), (.1 * iDurRand), SchannelName, (2200 * iFreqScale), (150 * iFreqScale), .11, iMeadowlarkDown, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (1.2 * iDurRand), (.1 * iDurRand), SchannelName, (3200 * iFreqScale), (1400 * iFreqScale), .11, giAvesRampDown, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (1.4 * iDurRand), (.05 * iDurRand), SchannelName, (2000 * iFreqScale), (200 * iFreqScale), .11, giAvesRampDown, giAvesMainAmp, iMeadowlarkHarm)
		schedulek("_Aves_oscbank", (1.5 * iDurRand), (.1 * iDurRand), SchannelName, (1600 * iFreqScale), (0 * iFreqScale), .11, giAvesRampDown, giAvesMainAmp, iMeadowlarkHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Scissor-tailed flycatcher (Tyrannus forficatus)
; https://en.wikipedia.org/wiki/Scissor-tailed_flycatcher
; Habitat: open shrubbery country with scattered trees
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_scissor_flycatcher, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; Species specific amp envelope
	iScissorFlyEnv = ftgenonce(0, 0, -1000, 7, 0, 400, 1, 200, 1, 400, 0)

	; Create partial harmonic amp ftables
	iScissorFlyHarm = ftgenonce(0, 0, -5, 2, .5, 1, .5, .1, .01)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_scissor_flycatcher-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.05 * iDurRand), SchannelName, (1800 * iFreqScale), (1800 * iFreqScale), .2, iScissorFlyEnv, giAvesMainAmp, iScissorFlyHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Great horned owl (Bubo virginianus)
; https://en.wikipedia.org/wiki/Great_horned_owl
; Habitat: trees bordering almost any landscape
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_great_horned_owl, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iHornedOwlUp = ftgenonce(0, 0, -1000, 7, 0, 300, 1, 700, 1)
	
	; Create partial harmonic amp ftables
	iHornedOwlHarm = ftgenonce(0, 0, 8, 2, 1, 0, .02, 0, 0, 0, .01, 0)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_great_horned_owl-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.1 * iDurRand), SchannelName, (300 * iFreqScale), (0 * iFreqScale), .1, giAvesMainAmp, giAvesMainAmp, iHornedOwlHarm)
		schedulek("_Aves_oscbank", (.3 * iDurRand), (.4 * iDurRand), SchannelName, (293 * iFreqScale), (6 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp, iHornedOwlHarm)
		schedulek("_Aves_oscbank", (1.45 * iDurRand), (.35 * iDurRand), SchannelName, (293 * iFreqScale), (7 * iFreqScale), .1, iHornedOwlUp, giAvesMainAmp, iHornedOwlHarm)
		schedulek("_Aves_oscbank", (2.2 * iDurRand), (.2 * iDurRand), SchannelName, (300 * iFreqScale), (-9 * iFreqScale), .1, iHornedOwlUp, giAvesMainAmp, iHornedOwlHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; ck-throated gray warbler (Setophaga nigrescens)
; https://en.wikipedia.org/wiki/Black-throated_gray_warbler
; Habitat: various forests with underbrush and scrub lands
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_gray_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iGrayWarbler1 = ftgenonce(0, 0, -1000, 7, \
		.5, 20, .6, 20, .45, 20, .62, 20, .4, 20, \
		.65, 20, .35, 20, .7, 40, .3, 20, \
		.7, 20, .3, 20, .7, 10, .2, 50, .8, 50, .1, 50, .9, 50, 0, 50, \
		1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, .5)
	iGrayWarbler2 = ftgenonce(0, 0, -1000, 7, 0, 10, .4, 10, 0, 10, .4, 10, \
		0, 10, .4, 10, 0, 10, .4, 10, 0, 10, .4, 10, 0, 150, .8, 150, .3, 150, \
		1, 150, 0, 150, .8, 150, .4)
	iGrayWarbler3 = ftgenonce(0, 0, -1000, 7, 1, 10, .6, 10, 1, 10, .6, 10, \
		1, 10, .6, 10, 1, 10, .6, 10, 1, 10, .6, 10, 1, 10, .6, 10, 1, 10, \
		.6, 10, 1, 10, .6, 10, 1, 10, .6, 10, 1, 10, .6, 10, 1, 10, .55, 10, \
		1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, \
		.5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, \
		1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, \
		.5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, 1, 10, .5, 10, \
		1, 10, .5, 10, 1, 400, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_gray_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.12 * iDurRand), SchannelName, (3700 * iFreqScale), (600 * iFreqScale), .05, iGrayWarbler1, giAvesMainAmp)
		schedulek("_Aves_osc", (.18 * iDurRand), (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .07, iGrayWarbler2, giAvesMainAmp)
		schedulek("_Aves_osc", (.28 * iDurRand), (.12 * iDurRand), SchannelName, (3700 * iFreqScale), (600 * iFreqScale), .12, iGrayWarbler1, giAvesMainAmp)
		schedulek("_Aves_osc", (.44 * iDurRand), (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .15, iGrayWarbler2, giAvesMainAmp)
		schedulek("_Aves_osc", (.54 * iDurRand), (.12 * iDurRand), SchannelName, (3700 * iFreqScale), (600 * iFreqScale), .2, iGrayWarbler1, giAvesMainAmp)
		schedulek("_Aves_osc", (.72 * iDurRand), (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .25, iGrayWarbler2, giAvesMainAmp)
		schedulek("_Aves_osc", (.82 * iDurRand), (.12 * iDurRand), SchannelName, (3700 * iFreqScale), (600 * iFreqScale), .25, iGrayWarbler1, giAvesMainAmp)
		schedulek("_Aves_osc", (.96 * iDurRand), (.2 * iDurRand), SchannelName, (3000 * iFreqScale), (2000 * iFreqScale), .2, iGrayWarbler3, giAvesMainAmp)
		schedulek("_Aves_osc", (1.2 * iDurRand), (.02 * iDurRand), SchannelName, (4500 * iFreqScale), (500 * iFreqScale), .05, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.25 * iDurRand), (.02 * iDurRand), SchannelName, (4200 * iFreqScale), (800 * iFreqScale), .05, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.3 * iDurRand), (.02 * iDurRand), SchannelName, (4000 * iFreqScale), (900 * iFreqScale), .05, giAvesRampUp, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; American yellow warbler (Setophaga petechia)
; https://en.wikipedia.org/wiki/American_yellow_warbler
; Habitat: near rivers and most other lands with many small trees
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_yellow_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iYellowWarbler1 = ftgenonce(0, 0, -1000, 7, 1, 50, 1, 550, 0, 20, .3, 20, .1)
	iYellowWarbler2 = ftgenonce(0, 0, -1000, 7, 0, 600, 1, 400, .5)
	iYellowWarbler3 = ftgenonce(0, 0, -1000, 7, 0, 300, .2, 500, .7, 200, .1)
	iYellowWarblerAmp = ftgenonce(0, 0, -1000, 7, 0, 900, 1, 100, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_yellow_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.05 * iDurRand), SchannelName, (5600 * iFreqScale), (400 * iFreqScale), .05, iYellowWarbler2, giAvesMainAmp)
		schedulek("_Aves_osc", (.23 * iDurRand), (.12 * iDurRand), SchannelName, (5000 * iFreqScale), (1500 * iFreqScale), .15, iYellowWarbler1, iYellowWarblerAmp)
		schedulek("_Aves_osc", (.45 * iDurRand), (.13 * iDurRand), SchannelName, (5000 * iFreqScale), (1700 * iFreqScale), .17, iYellowWarbler1, iYellowWarblerAmp)
		schedulek("_Aves_osc", (.62 * iDurRand), (.16 * iDurRand), SchannelName, (5000 * iFreqScale), (2000 * iFreqScale), .2, iYellowWarbler1, iYellowWarblerAmp)
		schedulek("_Aves_osc", (.85 * iDurRand), (.15 * iDurRand), SchannelName, (5000 * iFreqScale), (2000 * iFreqScale), .2, iYellowWarbler1, iYellowWarblerAmp)
		schedulek("_Aves_osc", (1.05 * iDurRand), (.075 * iDurRand), SchannelName, (3700 * iFreqScale), (1000 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.15 * iDurRand), (.075 * iDurRand), SchannelName, (3700 * iFreqScale), (800 * iFreqScale), .15, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.25 * iDurRand), (.075 * iDurRand), SchannelName, (3700 * iFreqScale), (800 * iFreqScale), .15, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.4 * iDurRand), (.2 * iDurRand), SchannelName, (3700 * iFreqScale), (2000 * iFreqScale), .2, iYellowWarbler3, iYellowWarblerAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Black-necked stilt (Himantopus mexicanus)
; https://en.wikipedia.org/wiki/Black-necked_stilt
; Habitat: near rivers, lakes and in other wetlands
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_black_stilt, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBlackStiltAmp = ftgenonce(0, 0, -1000, 7, 0, 900, 1, 100, 0)
	iBlackStiltUp = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, .2)
	
	; Create partial harmonic amp ftables
	iBlackStiltHarm = ftgenonce(0, 0, -5, 2, .5, 1, .75, .5, .1)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_black_stilt-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.1 * iDurRand), SchannelName, (900 * iFreqScale), (100 * iFreqScale), .2, iBlackStiltUp, iBlackStiltAmp, iBlackStiltHarm)
		schedulek("_Aves_oscbank", (.3 * iDurRand), (.1 * iDurRand), SchannelName, (900 * iFreqScale), (200 * iFreqScale), .2, iBlackStiltUp, iBlackStiltAmp, iBlackStiltHarm)
		schedulek("_Aves_oscbank", (.6 * iDurRand), (.1 * iDurRand), SchannelName, (900 * iFreqScale), (250 * iFreqScale), .2, iBlackStiltUp, iBlackStiltAmp, iBlackStiltHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Chestnut-sided warbler (Setophaga pensylvanica)
; https://en.wikipedia.org/wiki/Chestnut-sided_warbler
; Habitat: forests (with scrubs and bushes)
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_chestnut_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iChestnutWarblerY = ftgenonce(0, 0, -1000, 7, 1, 300, .5, 300, 1, 200, .2, 200, 0)
	iChestnutWarblerV = ftgenonce(0, 0, -1000, 7, .2, 500, 1, 500, 0)
	iChestnutWarblerW = ftgenonce(0, 0, -1000, 7, .5, 150, 0, 300, .1, 150, \
		1, 100, .9, 300, .9)
	iChestnutWarblerA = ftgenonce(0, 0, -1000, 7, 0, 950, 1, 50, 1)
	iChestnutWarblerB = ftgenonce(0, 0, -1000, 7, 1, 250, .3, 350, .15, 400, 0)
	iChestnutWarblerAmp1 = ftgenonce(0, 0, -1000, 7, 0, 900, 1, 100, 0)
	iChestnutWarblerAmp2 = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 300, .1, 100, \
		.9, 100, .1, 100, 1, 300, 0)
	
	; Create partial harmonic amp ftables
	iChestnutWarblerHarm = ftgenonce(0, 0, 2, 2, 1, .1)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_chestnut_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.1 * iDurRand), SchannelName, (4050 * iFreqScale), (1200 * iFreqScale), .05, iChestnutWarblerY, giAvesMainAmp, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.15 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (300 * iFreqScale), .07, iChestnutWarblerV, giAvesMainAmp, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.2 * iDurRand), (.1 * iDurRand), SchannelName, (4050 * iFreqScale), (1200 * iFreqScale), .15, iChestnutWarblerY, iChestnutWarblerAmp1, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.32 * iDurRand), (.03 * iDurRand), SchannelName, (3800 * iFreqScale), (500 * iFreqScale), .1, iChestnutWarblerV, giAvesMainAmp, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.4 * iDurRand), (.1 * iDurRand), SchannelName, (4000 * iFreqScale), (1200 * iFreqScale), .2, iChestnutWarblerY, giAvesTap, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.55 * iDurRand), (.03 * iDurRand), SchannelName, (3800 * iFreqScale), (500 * iFreqScale), .15, iChestnutWarblerV, giAvesMainAmp, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.62 * iDurRand), (.1 * iDurRand), SchannelName, (4000 * iFreqScale), (1200 * iFreqScale), .2, iChestnutWarblerY, giAvesTap, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.75 * iDurRand), (.03 * iDurRand), SchannelName, (3800 * iFreqScale), (500 * iFreqScale), .15, iChestnutWarblerV, giAvesMainAmp, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.81 * iDurRand), (.1 * iDurRand), SchannelName, (4000 * iFreqScale), (1200 * iFreqScale), .2, iChestnutWarblerY, giAvesTap, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (.95 * iDurRand), (.12 * iDurRand), SchannelName, (3800 * iFreqScale), (2200 * iFreqScale), .15, iChestnutWarblerW, iChestnutWarblerAmp2, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (1.1 * iDurRand), (.12 * iDurRand), SchannelName, (3800 * iFreqScale), (2200 * iFreqScale), .15, iChestnutWarblerW, iChestnutWarblerAmp2, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (1.25 * iDurRand), (.12 * iDurRand), SchannelName, (2500 * iFreqScale), (2200 * iFreqScale), .25, iChestnutWarblerA, iChestnutWarblerAmp1, iChestnutWarblerHarm)
		schedulek("_Aves_oscbank", (1.4 * iDurRand), (.12 * iDurRand), SchannelName, (2500 * iFreqScale), (4000 * iFreqScale), .15, iChestnutWarblerB, giAvesMainAmp, iChestnutWarblerHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Grasshopper sparrow (Ammodramus savannarum)
; https://en.wikipedia.org/wiki/Grasshopper_sparrow
; Habitat: open fields and prairie
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_grasshopper_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iGrasshopper1 = ftgenonce(0, 0, -1000, 7, .5, 20, .8, 20, .3, 20, .8, 10, \
		.1, 10, .9, 20, 0, 10, .9, 10, 0, 10, .9, 10, .1, 10, 1, 10, .1, 10, \
		1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, \
		.1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, \
		.1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, \
		1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, \
		.1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, \
		1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, \
		.1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, \
		1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, .1, 10, 1, 10, \
		.1, 10, 1, 10, .1, 10, 1, 10, \
		.1, 10, 1, 10, .1, 10, 1, 10, .1, 20, 1)
	iGrasshopper2 = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 100, 0, 100, 1, 100, \
		0, 100, 1, 100, 0, 100, 1, 100, 0, 100, 1, 100, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_grasshopper_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.01 * iDurRand), SchannelName, (8000 * iFreqScale), (100 * iFreqScale), .1, iGrasshopper2, giAvesMainAmp)
		schedulek("_Aves_osc", (.11 * iDurRand), (.01 * iDurRand), SchannelName, (5700 * iFreqScale), (300 * iFreqScale), .1, iGrasshopper2, giAvesMainAmp)
		schedulek("_Aves_osc", (.43 * iDurRand), (.01 * iDurRand), SchannelName, (3900 * iFreqScale), (100 * iFreqScale), .1, iGrasshopper2, giAvesMainAmp)
		schedulek("_Aves_osc", (.51 * iDurRand), (1.4 * iDurRand), SchannelName, (6000 * iFreqScale), (2500 * iFreqScale), .2, iGrasshopper1, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Swamp sparrow (Melospiza georgiana)
; https://en.wikipedia.org/wiki/Swamp_sparrow
; Habitat: marshes (including tidal marshes for one subspecies)
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_swamp_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iSwampUp = ftgenonce(0, 0, -1000, 7, 0, 600, .7, 300, 1)
	iSwampDown = ftgenonce(0, 0, -1000, 7, 1, 500, .5, 100, .6, 400, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_swamp_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	kIndex init 0
	if (kPlay == 1) then
		kIndex = 0
		while (kIndex < 1) do
			schedulek("_Aves_osc", (kIndex * iDurRand), (.02 * iDurRand), SchannelName, (3900 * iFreqScale), (200 * iFreqScale), .3, iSwampUp, giAvesMainAmp)
			schedulek("_Aves_osc", ((.035 + kIndex) * iDurRand), (.035 * iDurRand), SchannelName, (3200 * iFreqScale), (3000 * iFreqScale), .1, iSwampDown, giAvesMainAmp)
			schedulek("_Aves_osc", ((.08 + kIndex) * iDurRand), (.025 * iDurRand), SchannelName, (3700 * iFreqScale), (0 * iFreqScale), .1, giAvesMainAmp, giAvesMainAmp)
			kIndex += .1
		od
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Golden-crowned sparrow (Zonotrichia atricapilla)
; https://en.wikipedia.org/wiki/Golden-crowned_sparrow
; Habitat: brushy areas, shrubs
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_golden_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iGolden1 = ftgenonce(0, 0, -1000, 7, 1, 250, .2, 750, 0)
	iGolden2 = ftgenonce(0, 0, -1000, 7, .9, 50, 1, 50, .4, 900, 0)
	iGolden3 = ftgenonce(0, 0, -1000, 7, .5, 100, 0, 100, 1, 100, 0, 100, 1, \
		100, 0, 100, 1, 100, 0, 100, 1, 100, 0, 100, .5)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_golden_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.5 * iDurRand), SchannelName, (4300 * iFreqScale), (1000 * iFreqScale), .15, iGolden1, giAvesMainAmp)
		schedulek("_Aves_osc", (.7 * iDurRand), (.45 * iDurRand), SchannelName, (3300 * iFreqScale), (200 * iFreqScale), .15, iGolden1, giAvesMainAmp)
		schedulek("_Aves_osc", (1.15 * iDurRand), (.4 * iDurRand), SchannelName, (3800 * iFreqScale), (100 * iFreqScale), .15, iGolden2, giAvesMainAmp)
		schedulek("_Aves_osc", (1.6 * iDurRand), (.3 * iDurRand), SchannelName, (3800 * iFreqScale), (100 * iFreqScale), .1, iGolden2, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Indigo bunting (Passerina cyanea)
; https://en.wikipedia.org/wiki/Indigo_bunting
; Habitat: brushy forest edges, open deciduous woods, farmland
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_indigo_bunting, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBuntingV = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, 0)
	iBuntingY = ftgenonce(0, 0, -1000, 7, 1, 500, 0, 500, .9)
	iBuntingN = ftgenonce(0, 0, -1000, 7, .8, 300, 1, 400, .2, 300, 0)
	iBuntingZ = ftgenonce(0, 0, -1000, 7, 1, 100, .5, 150, .9, 750, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_indigo_bunting-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (700 * iFreqScale), .25, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.12 * iDurRand), (.02 * iDurRand), SchannelName, (6200 * iFreqScale), (1000 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.15 * iDurRand), (.15 * iDurRand), SchannelName, (3500 * iFreqScale), (2300 * iFreqScale), .1, iBuntingV, giAvesMainAmp)
		schedulek("_Aves_osc", (.34 * iDurRand), (.02 * iDurRand), SchannelName, (6200 * iFreqScale), (1800 * iFreqScale), .05, iBuntingZ, giAvesMainAmp)
		schedulek("_Aves_osc", (.4 * iDurRand), (.15 * iDurRand), SchannelName, (3400 * iFreqScale), (2300 * iFreqScale), .1, iBuntingV, giAvesMainAmp)
		schedulek("_Aves_osc", (.6 * iDurRand), (.1 * iDurRand), SchannelName, (3400 * iFreqScale), (800 * iFreqScale), .2, iBuntingV, giAvesMainAmp)
		schedulek("_Aves_osc", (.73 * iDurRand), (.03 * iDurRand), SchannelName, (4100 * iFreqScale), (2000 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.85 * iDurRand), (.08 * iDurRand), SchannelName, (3400 * iFreqScale), (800 * iFreqScale), .2, iBuntingV, giAvesMainAmp)
		schedulek("_Aves_osc", (1 * iDurRand), (.03 * iDurRand), SchannelName, (4100 * iFreqScale), (2000 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.1 * iDurRand), (.08 * iDurRand), SchannelName, (3700 * iFreqScale), (300 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.2 * iDurRand), (.1 * iDurRand), SchannelName, (4100 * iFreqScale), (2200 * iFreqScale), .15, iBuntingY, giAvesMainAmp)
		schedulek("_Aves_osc", (1.32 * iDurRand), (.05 * iDurRand), SchannelName, (3700 * iFreqScale), (300 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.41 * iDurRand), (.1 * iDurRand), SchannelName, (4100 * iFreqScale), (2200 * iFreqScale), .15, iBuntingY, giAvesMainAmp)
		schedulek("_Aves_osc", (1.54 * iDurRand), (.07 * iDurRand), SchannelName, (5200 * iFreqScale), (1800 * iFreqScale), .2, iBuntingN, giAvesMainAmp)
		schedulek("_Aves_osc", (1.65 * iDurRand), (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (1500 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.8 * iDurRand), (.07 * iDurRand), SchannelName, (5200 * iFreqScale), (1800 * iFreqScale), .2, iBuntingN, giAvesMainAmp)
		schedulek("_Aves_osc", (1.93 * iDurRand), (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (1500 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (2.03 * iDurRand), (.07 * iDurRand), SchannelName, (5200 * iFreqScale), (1800 * iFreqScale), .1, iBuntingN, giAvesMainAmp)
		schedulek("_Aves_osc", (2.11 * iDurRand), (.08 * iDurRand), SchannelName, (3000 * iFreqScale), (1500 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Hooded warbler (Setophaga citrina)
; https://en.wikipedia.org/wiki/Hooded_warbler
; Habitat: broadleaved woods with dense underbrush
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_hooded_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_hooded_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (1600 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.04 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (1700 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.2 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2000 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.24 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2000 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.33 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .15, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.37 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .15, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.45 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.49 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.57 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.61 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.79 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.83 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.91 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.95 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.03 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.07 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.15 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.2 * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (2100 * iFreqScale), .2, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.3 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.38 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.45 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.53 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.61 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.69 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.77 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.85 * iDurRand), (.04 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; American Widgeon (Mareca americana)
; https://en.wikipedia.org/wiki/American_wigeon
; Habitat: wetlands, northern forests and arcitc river deltas
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_american_widgeon, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iWidgeon1 = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, 0)
	
	; Create partial harmonic amp ftables
	iWidgeonHarm1 = ftgenonce(0, 0, 2, 2, 1, .02)
	iWidgeonHarm2 = ftgenonce(0, 0, 4, 2, .7, 1, .02, 0)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_american_widgeon-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.07 * iDurRand), SchannelName, (1900 * iFreqScale), (300 * iFreqScale), .15, iWidgeon1, iWidgeon1, iWidgeonHarm1)
		schedulek("_Aves_oscbank", (.1 * iDurRand), (.11 * iDurRand), SchannelName, (1700 * iFreqScale), (1400 * iFreqScale), .25, iWidgeon1, iWidgeon1, iWidgeonHarm2)
		schedulek("_Aves_oscbank", (.25 * iDurRand), (.07 * iDurRand), SchannelName, (1900 * iFreqScale), (300 * iFreqScale), .15, iWidgeon1, iWidgeon1, iWidgeonHarm1)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Louisiana waterthrush (Parkesia motacilla)
; https://en.wikipedia.org/wiki/Louisiana_waterthrush
; Habitat: near streams
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_louisiana_waterthrush, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iWaterthrush1 = ftgenonce(0, 0, -1000, 7, .8, 350, .4, 100, .9, 50, 1, 250, 1, 250, .1)
	iWaterthrush2 = ftgenonce(0, 0, -1000, 7, 1, 400, 0, 200, .1, 400, .8)
	iWaterthrush3 = ftgenonce(0, 0, -1000, 7, 1, 950, 0, 50, 0)
	iWaterthrushDamp = ftgenonce(0, 0, -1000, 7, 0, 900, 1, 100, 0)
	iWaterthrushAmp = ftgenonce(0, 0, -1000, 7, 0, 350, 1, 150, .2, 400, 1, 100, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_louisiana_waterthrush-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.17 * iDurRand), SchannelName, (4100 * iFreqScale), (2000 * iFreqScale), .2, iWaterthrush1, iWaterthrushAmp)
		schedulek("_Aves_osc", (.32 * iDurRand), (.18 * iDurRand), SchannelName, (4050 * iFreqScale), (2050 * iFreqScale), .3, iWaterthrush1, iWaterthrushAmp)
		schedulek("_Aves_osc", (.64 * iDurRand), (.2 * iDurRand), SchannelName, (4000 * iFreqScale), (1900 * iFreqScale), .25, iWaterthrush1, iWaterthrushAmp)
		schedulek("_Aves_osc", (.9 * iDurRand), (.2 * iDurRand), SchannelName, (3900 * iFreqScale), (2000 * iFreqScale), .3, iWaterthrush2, giAvesTap)
		schedulek("_Aves_osc", (1.25 * iDurRand), (.12 * iDurRand), SchannelName, (3000 * iFreqScale), (3000 * iFreqScale), .25, iWaterthrush3, iWaterthrushDamp)
		schedulek("_Aves_osc", (1.4 * iDurRand), (.1 * iDurRand), SchannelName, (2700 * iFreqScale), (1500 * iFreqScale), .2, giAvesRampUp, iWaterthrushDamp)
		schedulek("_Aves_osc", (1.58 * iDurRand), (.02 * iDurRand), SchannelName, (5200 * iFreqScale), (1000 * iFreqScale), .1, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.65 * iDurRand), (.02 * iDurRand), SchannelName, (5200 * iFreqScale), (1000 * iFreqScale), .1,  giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.7 * iDurRand), (.035 * iDurRand), SchannelName, (3200 * iFreqScale), (1000 * iFreqScale), .1, giAvesRampUp, iWaterthrushDamp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; (American) Robin (Turdus migratorius)
; https://en.wikipedia.org/wiki/American_robin
; Habitat: woodland, more open farmland, urban areas
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_robin, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iRobin1 = ftgenonce(0, 0, -1000, 7, 0, 120, .7, 180, 0, 500, 1, 200, .5)
	iRobin2 = ftgenonce(0, 0, -1000, 7, .1, 80, .7, 220, 0, 50, 1, 50, .3, 600, .3)
	iRobin3 = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 100, .7, 150, .7, 300, .3, 50, .5, 100, 0, 100, .2, 100, 0)
	iRobin4 = ftgenonce(0, 0, -1000, 7, .2, 250, 1, 350, .7, 300, 0, 100, .1)
	iRobin5 = giAvesRampDown
	iRobin6 = ftgenonce(0, 0, -1000, 7, .5, 100, 0, 100, .1, 100, 0, 100, 1, 100, 0, 100, 1, 100, .5, 300, .2)
	
	; Create partial harmonic amp ftables
	iRobinHarm = ftgenonce(0, 0, 2, 2, 1, .1)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_robin-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.06 * iDurRand), SchannelName, (2000 * iFreqScale), (800 * iFreqScale), .15, iRobin1, giAvesMainAmp, iRobinHarm)
		schedulek("_Aves_oscbank", (.11 * iDurRand), (.1 * iDurRand), SchannelName, (2000 * iFreqScale), (900 * iFreqScale), .15, iRobin2, giAvesMainAmp, iRobinHarm)
		schedulek("_Aves_oscbank", (.59 * iDurRand), (.24 * iDurRand), SchannelName, (2000 * iFreqScale), (2000 * iFreqScale), .25, iRobin3, giAvesMainAmp, iRobinHarm)
		schedulek("_Aves_oscbank", (1.18 * iDurRand), (.13 * iDurRand), SchannelName, (1900 * iFreqScale), (1600 * iFreqScale), .2, iRobin4, giAvesMainAmp, iRobinHarm)
		schedulek("_Aves_oscbank", (1.35 * iDurRand), (.11 * iDurRand), SchannelName, (2200 * iFreqScale), (1200 * iFreqScale), .25, iRobin5, giAvesMainAmp, iRobinHarm)
		schedulek("_Aves_oscbank", (1.86 * iDurRand), (.21 * iDurRand), SchannelName, (1950 * iFreqScale), (2000 * iFreqScale), .15, iRobin6, giAvesMainAmp, iRobinHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Solitary viero, possibly plumbeous vereo (Vireo plumbeus)
; https://en.wikipedia.org/wiki/Plumbeous_vireo
; Habitat: open pine forests
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_solitary_vireo, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iVireo1 = ftgenonce(0, 0, -1000, 7, .2, 30, .3, 30, .1, 40, .5, 30, .4, \
		30, .8, 30, .5, 30, .9, 30, .6, 30, 1, 30, .6, 30, 1, 30, .5, 40, .9, \
		40, .4, 40, .8, 20, .4, 30, .75, 30, .35, 30, .7, 30, .3, 30, .6, 30, \
		.25, 30, .5, 30, .2, 30, .3, 40, .1, 30, .3, 30, .05, 30, .3, 30, 0, \
		10, .3, 40, 0, 10, .1)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_solitary_vireo-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.4 * iDurRand), SchannelName, (1800 * iFreqScale), (1200 * iFreqScale), .2, iVireo1, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Pigeon hawk, Merlin (Falco columbarius)
; https://en.wikipedia.org/wiki/Merlin_(bird)
; Habitat: varied, preference: mix of low and medium height vegetation with
;	some trees, avoid dense forests
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_pigeon_hawk, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iPigeonHawk1 = ftgenonce(0, 0, -1000, 7, 0, 300, 1, 400, 1, 300, 0)
	
	; Create partial harmonic amp ftables
	iPigeonHawkHarm1 = ftgenonce(0, 0, 2, 2, .7, 1)
	iPigeonHawkHarm2 = ftgenonce(0, 0, 2, 2, .5, 1)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_pigeon_hawk-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	kIndex = 0
	if (kPlay == 1) then
		while (kIndex <14) do
			schedulek("_Aves_oscbank", (kIndex * .13 * iDurRand), (.1 * iDurRand), SchannelName, (1900 * iFreqScale), (200 * iFreqScale), .2, iPigeonHawk1, giAvesMainAmp, iPigeonHawkHarm1)
			schedulek("_Aves_oscbank", ((kIndex * .13 + .12) * iDurRand), (.01 * iDurRand), SchannelName, (2050 * iFreqScale), (0 * iFreqScale), .1, giAvesMainAmp, giAvesMainAmp, iPigeonHawkHarm2)
			kIndex += 1
		od
		schedulek("_Aves_oscbank", (1.82 * iDurRand), (.1 * iDurRand), SchannelName, (1900 * iFreqScale), (200 * iFreqScale), .2, iPigeonHawk1, giAvesMainAmp, iPigeonHawkHarm1)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Cerulean warbler (Setophaga cerulea)
; https://en.wikipedia.org/wiki/Cerulean_warbler
; Habitat: mature decideous forest
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_cerulean_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iCerulean1 = ftgenonce(0, 0, -1000, 7, .8, 100, 1, 150, .5, 150, 1, 150, .5, 150, 1, 300, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_cerulean_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.05 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .05, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.06 * iDurRand), (.05 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .075, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.14 * iDurRand), (.01 * iDurRand), SchannelName, (3200 * iFreqScale), (700 * iFreqScale), .07, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.15 * iDurRand), (.01 * iDurRand), SchannelName, (3200 * iFreqScale), (700 * iFreqScale), .08, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.16 * iDurRand), (.06 * iDurRand), SchannelName, (3200 * iFreqScale), (700 * iFreqScale), .09, giAvesRampDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.24 * iDurRand), (.06 * iDurRand), SchannelName, (3200 * iFreqScale), (500 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.33 * iDurRand), (.1 * iDurRand), SchannelName, (3000 * iFreqScale), (1200 * iFreqScale), .2, iCerulean1, giAvesMainAmp)
		schedulek("_Aves_osc", (.45 * iDurRand), (.05 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .2, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.53 * iDurRand), (.1 * iDurRand), SchannelName, (3000 * iFreqScale), (1200 * iFreqScale), .2, iCerulean1, giAvesMainAmp)
		schedulek("_Aves_osc", (.65 * iDurRand), (.05 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .2, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.73 * iDurRand), (.01 * iDurRand), SchannelName, (3900 * iFreqScale), (600 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.74 * iDurRand), (.01 * iDurRand), SchannelName, (3910 * iFreqScale), (800 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.75 * iDurRand), (.01 * iDurRand), SchannelName, (3940 * iFreqScale), (500 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.76 * iDurRand), (.01 * iDurRand), SchannelName, (4000 * iFreqScale), (500 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)

		; Looped part of the call
		kIndex = 0
		while (kIndex < 27) do
			schedulek("_Aves_osc", ((.77 + .01 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (3900 * iFreqScale), (1400 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
			kIndex += 1
		od
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Nashville warbler (Leiothlypis ruficapilla)
; https://en.wikipedia.org/wiki/Nashville_warbler
; Habitat: open mixed woods, bog habitats
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_nashville_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iNashvilleBlip = ftgenonce(0, 0, -1000, 7, .6, 350, 1, 650, 0)
	iNashvilleDown = ftgenonce(0, 0, -1000, 7, .9, 50, 1, 50, .9, 550, .5, 350, 0)
	iNashvilleUp = ftgenonce(0, 0, -1000, 7, 0, 150, .2, 100, .05, 650, .95, 50, 1)
	iNashvilleAmp = ftgenonce(0, 0, -1000, 7, 0, 800, 1, 200, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_nashville_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.025 * iDurRand), SchannelName, (3900 * iFreqScale), (300 * iFreqScale), .3, iNashvilleBlip, giAvesMainAmp)
		schedulek("_Aves_osc", (.09 * iDurRand), (.16 * iDurRand), SchannelName, (4200 * iFreqScale), (3800 * iFreqScale), .15, iNashvilleDown, iNashvilleAmp)
		schedulek("_Aves_osc", (.27 * iDurRand), (.025 * iDurRand), SchannelName, (3900 * iFreqScale), (300 * iFreqScale), .3, iNashvilleBlip, giAvesMainAmp)
		schedulek("_Aves_osc", (.4 * iDurRand), (.14 * iDurRand), SchannelName, (4300 * iFreqScale), (3700 * iFreqScale), .15, iNashvilleDown, iNashvilleAmp)
		schedulek("_Aves_osc", (.6 * iDurRand), (.03 * iDurRand), SchannelName, (3950 * iFreqScale), (350 * iFreqScale), .3, iNashvilleBlip, giAvesMainAmp)
		schedulek("_Aves_osc", (.66 * iDurRand), (.17 * iDurRand), SchannelName, (4200 * iFreqScale), (3900 * iFreqScale), .175, iNashvilleDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.85 * iDurRand), (.02 * iDurRand), SchannelName, (3800 * iFreqScale), (400 * iFreqScale), .25, iNashvilleBlip, giAvesMainAmp)
		schedulek("_Aves_osc", (.96 * iDurRand), (.14 * iDurRand), SchannelName, (4200 * iFreqScale), (3800 * iFreqScale), .165, iNashvilleDown, iNashvilleAmp)
		schedulek("_Aves_osc", (1.15 * iDurRand), (.03 * iDurRand), SchannelName, (3750 * iFreqScale), (300 * iFreqScale), .2, iNashvilleBlip, giAvesMainAmp)
		schedulek("_Aves_osc", (1.25 * iDurRand), (.11 * iDurRand), SchannelName, (4200 * iFreqScale), (3700 * iFreqScale), .1, iNashvilleDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.42 * iDurRand), (.1 * iDurRand), SchannelName, (3800 * iFreqScale), (2200 * iFreqScale), .1, iNashvilleUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.55 * iDurRand), (.1 * iDurRand), SchannelName, (3800 * iFreqScale), (2150 * iFreqScale), .125, iNashvilleUp, giAvesMainAmp)
		schedulek("_Aves_osc", (1.7 * iDurRand), (.075 * iDurRand), SchannelName, (3900 * iFreqScale), (1800 * iFreqScale), .1, iNashvilleUp, iNashvilleAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Eastern phoebe (Sayornis phoebe)
; https://en.wikipedia.org/wiki/Eastern_phoebe
; Habitat: urban, woodlands, especially near streams, avoid open land
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_eastern_phoebe, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iPhoebe1 = ftgenonce(0, 0, -1000, 7, 0, 300, .3, 50, .5, 200, .4, 150, .8, 50, .7, 50, 1, 150, .9, 50, 0)
	iPhoebe2 = ftgenonce(0, 0, -1000, 7, 0, 50, 1, 950, 0)
	iPhoebe3 = ftgenonce(0, 0, -1000, 7, 0, 100, .4, 700, 1, 200, .1)
	iPhoebe4 = ftgenonce(0, 0, -1000, 7, 1, 50, .7, 950, 0)
	iPhoebeAmp = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 900, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_eastern_phoebe-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.225 * iDurRand), SchannelName, (3000 * iFreqScale), (1300 * iFreqScale), .3, iPhoebe1, giAvesMainAmp)
		schedulek("_Aves_osc", (.35 * iDurRand), (.12 * iDurRand), SchannelName, (3000 * iFreqScale), (500 * iFreqScale), .1, iPhoebe2, iPhoebeAmp)
		schedulek("_Aves_osc", (.4 * iDurRand), (.1 * iDurRand), SchannelName, (3000 * iFreqScale), (1500 * iFreqScale), .2, iPhoebe3, iPhoebeAmp)
		schedulek("_Aves_osc", (.55 * iDurRand), (.05 * iDurRand), SchannelName, (3000 * iFreqScale), (1400 * iFreqScale), .2, iPhoebe4, iPhoebeAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Painted bunting (Passerina ciris)
; https://en.wikipedia.org/wiki/Painted_bunting
; Habitat: woodlands edges, thickets, brush/scrubs (near rivers)
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_painted_bunting, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBuntingUp = giAvesRampUp
	iBuntingDown = giAvesRampDown
	iBunting3 = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, 0)
	iBunting4 = ftgenonce(0, 0, -1000, 7, .7, 150, 0, 250, 1, 400, 1, 200, .5)
	iBunting5 = ftgenonce(0, 0, -1000, 7, 1, 250, .4, 500, .5, 250, 0)
	iBunting6 = ftgenonce(0, 0, -1000, 7, .3, 400, .4, 100, 1, 100, .2, 400, 0)
	iBunting7 = ftgenonce(0, 0, -1000, 7, .4, 250, 0, 100, 1, 150, 0, 150, 1, 100, 0, 100, 1, 150, 0)
	iBunting8 = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, .5)
	iBunting9 = ftgenonce(0, 0, -1000, 7, .3, 300, 1, 300, .3, 400, 0)
	iBuntingAmp1 = ftgenonce(0, 0, -1000, 7, 0, 900, 1, 100, 0)
	iBuntingAmp2 = ftgenonce(0, 0, -1000, 7, 0, 100, .5, 50, 0, 250, 1, 500, 1, 100, 0)
	iBuntingAmp3 = ftgenonce(0, 0, -1000, 7, 0, 50, 1, 250, 1, 200, .3, 400, 1, 100, 0)
	iBuntingAmp4 = ftgenonce(0, 0, -1000, 7, 0, 50, 1, 250, .2, 300, .2, 300, 1, 100, 0)
	iBuntingAmp5 = ftgenonce(0, 0, -1000, 7, 0, 100, .5, 400, .5, 400, 1, 100, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_painted_bunting-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.1 * iDurRand), SchannelName, (3100 * iFreqScale), (900 * iFreqScale), .05, iBuntingUp, iBuntingAmp1)
		schedulek("_Aves_osc", (.16 * iDurRand), (.07 * iDurRand), SchannelName, (4100 * iFreqScale), (700 * iFreqScale), .15, iBuntingDown, giAvesMainAmp)
		schedulek("_Aves_osc", (.31 * iDurRand), (.12 * iDurRand), SchannelName, (3700 * iFreqScale), (1000 * iFreqScale), .2, iBunting3, giAvesMainAmp)
		schedulek("_Aves_osc", (.47 * iDurRand), (.08 * iDurRand), SchannelName, (2300 * iFreqScale), (1600 * iFreqScale), .15, iBunting4, iBuntingAmp2)
		schedulek("_Aves_osc", (.63 * iDurRand), (.1 * iDurRand), SchannelName, (4000 * iFreqScale), (1000 * iFreqScale), .25, iBuntingUp, giAvesTap)
		schedulek("_Aves_osc", (.75 * iDurRand), (.12 * iDurRand), SchannelName, (2300 * iFreqScale), (1700 * iFreqScale), .2, iBunting5, giAvesMainAmp)
		schedulek("_Aves_osc", (.91 * iDurRand), (.15 * iDurRand), SchannelName, (3800 * iFreqScale), (2200 * iFreqScale), .3, iBunting6, iBuntingAmp3)
		schedulek("_Aves_osc", (1.13 * iDurRand), (.1 * iDurRand), SchannelName, (2300 * iFreqScale), (1600 * iFreqScale), .15, iBunting7, giAvesMainAmp)
		schedulek("_Aves_osc", (1.25 * iDurRand), (.02 * iDurRand), SchannelName, (3200 * iFreqScale), (1000 * iFreqScale), .1, iBuntingDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.28 * iDurRand), (.02 * iDurRand), SchannelName, (3200 * iFreqScale), (1000 * iFreqScale), .1, iBuntingDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.31 * iDurRand), (.02 * iDurRand), SchannelName, (3200 * iFreqScale), (1000 * iFreqScale), .1, iBuntingDown, giAvesMainAmp)
		schedulek("_Aves_osc", (1.35 * iDurRand), (.03 * iDurRand), SchannelName, (4000 * iFreqScale), (2000 * iFreqScale), .12, iBunting8, iBuntingAmp4)
		schedulek("_Aves_osc", (1.42 * iDurRand), (.1 * iDurRand), SchannelName, (2300 * iFreqScale), (1700 * iFreqScale), .2, iBunting9, iBuntingAmp5)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Western flycatcher, either pacific-slope or cordilleran (Empidonax difficilis)
; https://en.wikipedia.org/wiki/Pacific-slope_flycatcher
; Habitat: woods and forests (coniferous or deciduous)
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_western_flycatcher, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iFlycatcher1 = ftgenonce(0, 0, -1000, 7, 0, 100, .1, 100, .4, 750, .1, 50, 0)
	iFlycatcher2 = ftgenonce(0, 0, -1000, 7, .5, 250, 1, 250, 0, 100, 0, 350, .3, 50, .6)
	iFlycatcherAmp1 = ftgenonce(0, 0, -1000, 7, 0, 100, .2, 100, .1, 100, 1, 600, 1, 100, 0)
	iFlycatcherAmp2 = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 100, 1, 300, .1, 100, .1, 300, 1, 100, 0)
	
	; Create partial harmonic amp ftables
	iFlycatcherHarm = ftgenonce(0, 0, 4, 2, 1, .02, .1, .01)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_western_flycatcher-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.2 * iDurRand), SchannelName, (2000 * iFreqScale), (2200 * iFreqScale), .2, iFlycatcher1, iFlycatcherAmp1, iFlycatcherHarm)
		schedulek("_Aves_oscbank", (.3 * iDurRand), (.2 * iDurRand), SchannelName, (2000 * iFreqScale), (1100 * iFreqScale), .2, iFlycatcher2, iFlycatcherAmp2, iFlycatcherHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Bachman\s sparrow (Peucaea aestivalis)
; https://en.wikipedia.org/wiki/Bachman%27s_sparrow
; Habitat: areas with dense undergrowth, scrubs, open pine forests
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_bachmans_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iSparrow1 = ftgenonce(0, 0, -1000, 7, 1, 100, .5, 800, .5, 100, 0)
	iSparrowUp = ftgenonce(0, 0, -1000, 7, .1, 350, 0, 650, 1)
	iSparrowDown = ftgenonce(0, 0, -1000, 7, 1, 400, .5, 600, 0)
	iSparrowLast = ftgenonce(0, 0, -1000, 7, 1, 250, 0, 500, .4, 250, .5)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_bachmans_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.51 * iDurRand), SchannelName, (4900 * iFreqScale), (200 * iFreqScale), .3, iSparrow1, giAvesMainAmp)
		schedulek("_Aves_osc", (.52 * iDurRand), (.015 * iDurRand), SchannelName, (3800 * iFreqScale), (200 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.52 * iDurRand), (.015 * iDurRand), SchannelName, (3750 * iFreqScale), (250 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.54 * iDurRand), (.015 * iDurRand), SchannelName, (3600 * iFreqScale), (300 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.56 * iDurRand), (.015 * iDurRand), SchannelName, (3500 * iFreqScale), (250 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.58 * iDurRand), (.015 * iDurRand), SchannelName, (3400 * iFreqScale), (200 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.6 * iDurRand), (.015 * iDurRand), SchannelName, (3200 * iFreqScale), (200 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)
		schedulek("_Aves_osc", (.62 * iDurRand), (.015 * iDurRand), SchannelName, (3800 * iFreqScale), (100 * iFreqScale), .1, iSparrowUp, giAvesMainAmp)

		kIndex = 0
		while (kIndex <7) do
			schedulek("_Aves_osc", ((.65 + kIndex * .15) * iDurRand), (.07 * iDurRand), SchannelName, (3000 * iFreqScale), (750 * iFreqScale), .2, iSparrowUp, giAvesMainAmp)
			schedulek("_Aves_osc", ((.73 + kIndex * .15) * iDurRand), (.03 * iDurRand), SchannelName, (5200 * iFreqScale), (1000 * iFreqScale), .1, iSparrowDown, giAvesMainAmp)
			kIndex += 1
		od

		kIndex = 0
		while (kIndex <5) do
			schedulek("_Aves_osc", ((2.8 + .1 * kIndex) * iDurRand), (.06 * iDurRand), SchannelName, (4000 * iFreqScale), (1700 * iFreqScale), .1, giAvesRampUp, giAvesMainAmp)
			schedulek("_Aves_osc", ((2.87 + .1 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (5200 * iFreqScale), (0 * iFreqScale), .2, giAvesRampUp, giAvesMainAmp)
			kIndex += 1
		od

		kIndex = 0
		while (kIndex <6) do
			schedulek("_Aves_osc", ((3.4 + .2 * kIndex) * iDurRand), (.15 * iDurRand), SchannelName, (3000 * iFreqScale), (1000 * iFreqScale), .2, iSparrowLast, giAvesMainAmp)
			kIndex += 1
		od
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Cedar waxwing (Bombycilla cedrorum)
; https://en.wikipedia.org/wiki/Cedar_waxwing
; Habitat: edge of woods, open forest
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_cedar_waxwing, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iCedar1 = ftgenonce(0, 0, -1000, 7, 0, 250, .7, 450, 1, 200, 1, 100, .2)
	iCedarAmp = ftgenonce(0, 0, -1000, 7, 0, 200, 1, 200, 1, 600, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_cedar_waxwing-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.5 * iDurRand), SchannelName, (6000 * iFreqScale), (800 * iFreqScale), .2, iCedar1, iCedarAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Baird's sparrow (Centronyx bairdii)
; https://en.m.wikipedia.org/wiki/Baird%27s_sparrow
; Habitat: grassland, prairie
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_bairds_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iSparrowEnd = ftgenonce(0, 0, -1000, 7, 0, 250, 1, 250, 0, 250, 1, 250, 0)
	iSparrowStart = ftgenonce(0, 0, -1000, 7, .5, 50, 1, 50, 0, 50, 1, 50, 0, \
		50, 1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, \
		1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_bairds_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.09 * iDurRand), SchannelName, (6500 * iFreqScale), (1500 * iFreqScale), .2, iSparrowStart, giAvesMainAmp)
		schedulek("_Aves_osc", (.22 * iDurRand), (.01 * iDurRand), SchannelName, (5900 * iFreqScale), (100 * iFreqScale), .2, iSparrowEnd, giAvesMainAmp)
		schedulek("_Aves_osc", (.25 * iDurRand), (.09 * iDurRand), SchannelName, (6000 * iFreqScale), (1000 * iFreqScale), .2, iSparrowStart, giAvesMainAmp)
		schedulek("_Aves_osc", (.45 * iDurRand), (.01 * iDurRand), SchannelName, (4200 * iFreqScale), (100 * iFreqScale), .2, iSparrowEnd, giAvesMainAmp)
		schedulek("_Aves_osc", (.5 * iDurRand), (.08 * iDurRand), SchannelName, (4200 * iFreqScale), (600 * iFreqScale), .2, iSparrowStart, giAvesMainAmp)
		schedulek("_Aves_osc", (.59 * iDurRand), (.01 * iDurRand), SchannelName, (4400 * iFreqScale), (100 * iFreqScale), .2, iSparrowEnd, giAvesMainAmp)
		schedulek("_Aves_osc", (.6 * iDurRand), (.01 * iDurRand), SchannelName, (4400 * iFreqScale), (100 * iFreqScale), .2, iSparrowEnd, giAvesMainAmp)
		schedulek("_Aves_osc", (.68 * iDurRand), (.07 * iDurRand), SchannelName, (5400 * iFreqScale), (700 * iFreqScale), .2, iSparrowStart, giAvesMainAmp)

		kIndex = 0
		while (kIndex <15) do
			schedulek("_Aves_osc", ((.75 + .08 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (4200 * iFreqScale), (100 * iFreqScale), (.2 - .01 * kIndex), iSparrowEnd, giAvesMainAmp)
			schedulek("_Aves_osc", ((.79 + .08 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (4400 * iFreqScale), (100 * iFreqScale), (.2 - .01 * kIndex), iSparrowEnd, giAvesMainAmp)
			kIndex += 1
		od

		schedulek("_Aves_osc", (1.97 * iDurRand), (.01 * iDurRand), SchannelName, (4200 * iFreqScale), (100 * iFreqScale), .05, iSparrowEnd, giAvesMainAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Kentucky warbler (Geothlypis formosa)
; https://en.wikipedia.org/wiki/Kentucky_warbler
; Habitat: Deciduous forest
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_kentucky_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iKentuckyStart = ftgenonce(0, 0, -1000, 7, .3, 500, 1, 500, 0)
	iKentuckyDown = ftgenonce(0, 0, -1000, 7, .9, 100, 1, 900, 0)
	iKentuckyTrill = ftgenonce(0, 0, -1000, 7, 1, 250, 0, 250, 0, 250, 1, 250, 0)
	
	; Create partial harmonic amp ftables
	iKentuckyHarm0 = ftgenonce(0, 0, 2, 2, 1, .03)
	iKentuckyHarm1 = ftgenonce(0, 0, 2, 2, 1, .01)
	iKentuckyHarm2 = ftgenonce(0, 0, 2, 2, 1, .1)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_kentucky_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.02 * iDurRand), SchannelName, (3800 * iFreqScale), (200 * iFreqScale), .05, iKentuckyStart, giAvesMainAmp, iKentuckyHarm0)
		schedulek("_Aves_oscbank", (.05 * iDurRand), (.03 * iDurRand), SchannelName, (4300 * iFreqScale), (200 * iFreqScale), .15,giAvesRampUp, giAvesMainAmp, iKentuckyHarm2)
		schedulek("_Aves_oscbank", (.08 * iDurRand), (.02 * iDurRand), SchannelName, (3200 * iFreqScale), (100 * iFreqScale), .1, iKentuckyDown, giAvesMainAmp, iKentuckyHarm2)
		
		kIndex = 0
		while (kIndex <4) do
			schedulek("_Aves_oscbank", ((.15 + .35 * kIndex) * iDurRand), (.05 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .15, iKentuckyStart, giAvesMainAmp, iKentuckyHarm1)
			schedulek("_Aves_oscbank", ((.22 + .35 * kIndex) * iDurRand), (.06 * iDurRand), SchannelName, (3100 * iFreqScale), (1200 * iFreqScale), .1, iKentuckyDown, giAvesMainAmp, iKentuckyHarm1)
			schedulek("_Aves_oscbank", ((.3 + .35 * kIndex) * iDurRand), (.06 * iDurRand), SchannelName, (3200 * iFreqScale), (1200 * iFreqScale), .1, iKentuckyDown, giAvesMainAmp, iKentuckyHarm1)
			schedulek("_Aves_oscbank", ((.38 + .35 * kIndex) * iDurRand), (.05 * iDurRand), SchannelName, (4600 * iFreqScale), (100 * iFreqScale), .2, iKentuckyTrill, giAvesMainAmp, iKentuckyHarm2)
			kIndex += 1
		od
		
		kIndex = 0
		while (kIndex < 2) do
			schedulek("_Aves_oscbank", ((1.45 + .25 * kIndex) * iDurRand), (.05 * iDurRand), SchannelName, (2800 * iFreqScale), (800 * iFreqScale), .15, iKentuckyStart, giAvesMainAmp, iKentuckyHarm1)
			schedulek("_Aves_oscbank", ((1.52 + .25 * kIndex) * iDurRand), (.06 * iDurRand), SchannelName, (2700 * iFreqScale), (1200 * iFreqScale), .1, iKentuckyDown, giAvesMainAmp, iKentuckyHarm1)
			schedulek("_Aves_oscbank", ((1.6  + .25 * kIndex) * iDurRand), (.05 * iDurRand), SchannelName, (4700 * iFreqScale), (100 * iFreqScale), .25, iKentuckyTrill, giAvesMainAmp, iKentuckyHarm2)
			kIndex += 1
		od
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; (eastern?) Rufous-sided towhee (Pipilo erythrophthalmus)
; https://en.wikipedia.org/wiki/Eastern_towhee
; Habitat: brushy areas
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_rufous_towhee, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iTowhee1 = ftgenonce(0, 0, -1000, 7, .1, 20, .05, 20, .15, 20, .05, 20, .2, 20, \
		.04, 20, .25, 20, .03, 20, .3, 20, .02, 20, \
		.35, 20, .01, 20, .4, 20, 0, 20, .45, 20, \
		0, 20, .5, 20, 0, 20, .5, 440, 1, 200, 0)
	iTowhee2 = giAvesRampUp
	iTowhee3 = giAvesRampDown
	iTowheeVol = ftgenonce(0, 0, -10, -2, .1, .09, .1, .09, .08, .08, .07, .06, .05, .03)
	
	; Create partial harmonic amp ftables
	iTowheeHarm = ftgenonce(0, 0, -3, 2, .03, 1, .03)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_rufous_towhee-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.13 * iDurRand), SchannelName, (1400 * iFreqScale), (1100 * iFreqScale), .2, iTowhee1, giAvesMainAmp, iTowheeHarm)
		schedulek("_Aves_oscbank", (.2 * iDurRand), (.13 * iDurRand), SchannelName, (1400 * iFreqScale), (1100 * iFreqScale), .2, iTowhee1, giAvesMainAmp, iTowheeHarm)
		schedulek("_Aves_oscbank", (.35 * iDurRand), (.13 * iDurRand), SchannelName, (1400 * iFreqScale), (1100 * iFreqScale), .2, iTowhee1, giAvesMainAmp, iTowheeHarm)
		schedulek("_Aves_oscbank", (.5 * iDurRand), (.1 * iDurRand), SchannelName, (1400 * iFreqScale), (1100 * iFreqScale), .2, iTowhee1, giAvesMainAmp, iTowheeHarm)

		kIndex = 0
		while (kIndex <10) do
			schedulek("_Aves_osc", ((.63 + .065 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (5100 * iFreqScale), (2000 * iFreqScale), tab(kIndex, iTowheeVol, 0), iTowhee2, giAvesMainAmp)
			schedulek("_Aves_osc", ((.645 + .065 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (5100 * iFreqScale), (1600 * iFreqScale), tab(kIndex, iTowheeVol, 0), iTowhee2, giAvesMainAmp)
			schedulek("_Aves_osc", ((.66 + .065 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (5100 * iFreqScale), (1000 * iFreqScale), tab(kIndex, iTowheeVol, 0), iTowhee2, giAvesMainAmp)
			schedulek("_Aves_osc", ((.68 + .065 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (3000 * iFreqScale), (1200 * iFreqScale), tab(kIndex, iTowheeVol, 0), iTowhee3, giAvesMainAmp)
			kIndex += 1
		od
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Prothonotary warbler (Protonotaria citrea)
; https://en.wikipedia.org/wiki/Prothonotary_warbler
; Habitat: deciduous forest (hardwood swamps)
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_prothonotary, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iPro1 = ftgenonce(0, 0, -1000, 7, .1, 200, 0, 800, 1)
	iPro2 = giAvesRampUp
	iProAmp = ftgenonce(0, 0, -1000, 7, 0, 200, 1, 200, .5, 600, 0)

	; default values
	iFreq1 = 3000 * iFreqScale
	iFreq2 = 4000 * iFreqScale
	iFM1 = 3000 * iFreqScale
	iFM2 = 2500 * iFreqScale
	iDur1 = .08 * iDurRand
	iDur2 = .05 * iDurRand
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_prothonotary-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, iDur1, SchannelName, iFreq1, iFM1, .05, iPro1, iProAmp)
		schedulek("_Aves_osc", (.09 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .06, iPro2, giAvesAmp)
		schedulek("_Aves_osc", (.2 * iDurRand), iDur1, SchannelName, iFreq1, iFM1, .1, iPro1, iProAmp)
		schedulek("_Aves_osc", (.3 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .1, iPro2, giAvesAmp)
		schedulek("_Aves_osc", (.5 * iDurRand), iDur1, SchannelName, iFreq1, iFM1, .15, iPro1, iProAmp)
		schedulek("_Aves_osc", (.59 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .16, iPro2, giAvesAmp)
		schedulek("_Aves_osc", (.78 * iDurRand), iDur1, SchannelName, iFreq1, iFM1, .2, iPro1, iProAmp)
		schedulek("_Aves_osc", (.87 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .19, iPro2, giAvesAmp)
		schedulek("_Aves_osc", (1.04 * iDurRand), iDur1, SchannelName, iFreq1, iFM1, .2, iPro1, iProAmp)
		schedulek("_Aves_osc", (1.13 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .16, iPro2, giAvesAmp)
		schedulek("_Aves_osc", (1.27 * iDurRand), iDur1, SchannelName, iFreq1, iFM1, .15, iPro1, iProAmp)
		schedulek("_Aves_osc", (1.36 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .1, iPro2, giAvesAmp)
		schedulek("_Aves_osc", (1.54 * iDurRand), iDur1, SchannelName, iFreq1, iFM1, .1, iPro1, iProAmp)
		schedulek("_Aves_osc", (1.63 * iDurRand), iDur2, SchannelName, iFreq2, iFM2, .06, iPro2, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Audubon's warbler (Setophaga auduboni)
; https://en.wikipedia.org/wiki/Audubon%27s_warbler
; Habitat: Coniferous and mixed woodland
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_audubons_warbler, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iAudubon1 = ftgenonce(0, 0, -1000, 7, .1, 500, 1, 500, 0)
	iAudubonEnd = ftgenonce(0, 0, -1000, 7, 0, 150, 1, 300, .9, 50, 0, 50, 1, 450, .9, 100, .1)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_audubons_warbler-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.04 * iDurRand), SchannelName, (2400 * iFreqScale), (200 * iFreqScale), .05, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.08 * iDurRand), (.03 * iDurRand), SchannelName, (3200 * iFreqScale), (200 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.15 * iDurRand), (.04 * iDurRand), SchannelName, (2500 * iFreqScale), (300 * iFreqScale), .15, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.22 * iDurRand), (.04 * iDurRand), SchannelName, (2300 * iFreqScale), (600 * iFreqScale), .15, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.27 * iDurRand), (.03 * iDurRand), SchannelName, (3500 * iFreqScale), (400 * iFreqScale), .2, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.31 * iDurRand), (.04 * iDurRand), SchannelName, (2300 * iFreqScale), (1200 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.38 * iDurRand), (.05 * iDurRand), SchannelName, (2300 * iFreqScale), (1200 * iFreqScale), .15, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.47 * iDurRand), (.02 * iDurRand), SchannelName, (3200 * iFreqScale), (800 * iFreqScale), .25, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.5 * iDurRand), (.08 * iDurRand), SchannelName, (2400 * iFreqScale), (600 * iFreqScale), .2, iAudubon1, giAvesAmp)
		schedulek("_Aves_osc", (.6 * iDurRand), (.02 * iDurRand), SchannelName, (2200 * iFreqScale), (400 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.63 * iDurRand), (.07 * iDurRand), SchannelName, (2400 * iFreqScale), (1400 * iFreqScale), .15, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.72 * iDurRand), (.03 * iDurRand), SchannelName, (3000 * iFreqScale), (800 * iFreqScale), .2, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.75 * iDurRand), (.03 * iDurRand), SchannelName, (2500 * iFreqScale), (400 * iFreqScale), .1, iAudubon1, giAvesAmp)
		schedulek("_Aves_osc", (.8 * iDurRand), (.01 * iDurRand), SchannelName, (2300 * iFreqScale), (100 * iFreqScale), .05, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.81 * iDurRand), (.06 * iDurRand), SchannelName, (2200 * iFreqScale), (1400 * iFreqScale), .15, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.9 * iDurRand), (.03 * iDurRand), SchannelName, (3100 * iFreqScale), (800 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.95 * iDurRand), (.07 * iDurRand), SchannelName, (2800 * iFreqScale), (800 * iFreqScale), .15, iAudubon1, giAvesAmp)
		schedulek("_Aves_osc", (1.04 * iDurRand), (.06 * iDurRand), SchannelName, (2400 * iFreqScale), (1000 * iFreqScale), .1, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (1.11 * iDurRand), (.14 * iDurRand), SchannelName, (3100 * iFreqScale), (900 * iFreqScale), .25, iAudubonEnd, giAvesAmp)
		schedulek("_Aves_osc", (1.27 * iDurRand), (.12 * iDurRand), SchannelName, (3200 * iFreqScale), (800 * iFreqScale), .2, iAudubonEnd, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Lark bunting (Calamospiza melanocorys)
; https://en.wikipedia.org/wiki/Lark_bunting
; Habitat: grassland, prairie
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_lark_bunting, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBunting1 = ftgenonce(0, 0, -1000, 7, 0, 60, .8, 60, 0, 60, .85, 60, .05, \
		120, .9, 60, .1, 60, .95, 60, .2, 60, 1, 60, .2, 60, 1, 60, .2, 60, 1, \
		60, .2, 100, 1)
	iBunting2 = ftgenonce(0, 0, -1000, 7, 0, 50, .8, 50, 0, 50, .85, 50, 0, 50, \
		.9, 50, 0, 50, .95, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0, 50, \
		1, 50, 0, 50, 1, 50, 0, 50, 1, 50, 0)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_lark_bunting-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.03 * iDurRand), SchannelName, (1800 * iFreqScale), (100 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.1 * iDurRand), (.12 * iDurRand), SchannelName, (1700 * iFreqScale), (400 * iFreqScale), .2, giAvesRampUp, giAvesAmp)

		kIndex = 0
		while (kIndex <7) do
			schedulek("_Aves_osc", ((.3 + .2 * kIndex) * iDurRand), (.03 * iDurRand), SchannelName, (4100 * iFreqScale), (500 * iFreqScale), .15, giAvesRampDown, giAvesAmp)
			schedulek("_Aves_osc", ((.35 + .2 * kIndex) * iDurRand), (.05 * iDurRand), SchannelName, (2000 * iFreqScale), (400 * iFreqScale), .2, giAvesRampDown, giAvesAmp)
			schedulek("_Aves_osc", ((.41 + .2 * kIndex) * iDurRand), (.03 * iDurRand), SchannelName, (1800 * iFreqScale), (100 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
			kIndex += 1
		od

		schedulek("_Aves_osc", (1.67 * iDurRand), (.23 * iDurRand), SchannelName, (6000 * iFreqScale), (600 * iFreqScale), .15, iBunting1, giAvesAmp)
		schedulek("_Aves_osc", (1.995 * iDurRand), (.28 * iDurRand), SchannelName, (6000 * iFreqScale), (600 * iFreqScale), .15, iBunting2, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Eastern bluebird (Sialia sialis)
; https://en.wikipedia.org/wiki/Eastern_bluebird
; Habitat: open country near trees, sparse ground cover
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_eastern_bluebird, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBluebird1 = ftgenonce(0, 0, -1000, 7, .6, 100, 1, 100, 0, 50, 1, 50, 0, 50, \
		1, 50, 0, 50, 1, 50, 0, 250, 1, 250, 0)
	iBluebird2 = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, 0)
	iBluebird3 = ftgenonce(0, 0, -1000, 7, .5, 100, 1, 100, 0, 150, 1, 150, 0, \
		150, 1, 150, 0, 150, 1, 50, .5)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_eastern_bluebird-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.02 * iDurRand), SchannelName, (2000 * iFreqScale), (1600 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.05 * iDurRand), (.02 * iDurRand), SchannelName, (2000 * iFreqScale), (1600 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.11 * iDurRand), (.02 * iDurRand), SchannelName, (2000 * iFreqScale), (1600 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.25 * iDurRand), (.13 * iDurRand), SchannelName, (2000 * iFreqScale), (1400 * iFreqScale), .2, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.45 * iDurRand), (.24 * iDurRand), SchannelName, (2000 * iFreqScale), (800 * iFreqScale), .2, iBluebird1, giAvesAmp)
		schedulek("_Aves_osc", (.93 * iDurRand), (.03 * iDurRand), SchannelName, (2200 * iFreqScale), (400 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.97 * iDurRand), (.1 * iDurRand), SchannelName, (1950 * iFreqScale), (100 * iFreqScale), .15, iBluebird2, giAvesAmp)
		schedulek("_Aves_osc", (1.21 * iDurRand), (.15 * iDurRand), SchannelName, (2000 * iFreqScale), (600 * iFreqScale), .2, iBluebird3, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Chuck-will's-widow (Antrostomus carolinensis)
; https://en.wikipedia.org/wiki/Chuck-will%27s-widow
; Habitat: near swamps, rocky uplands and pine woods
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_wills_widow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iWidow1 = ftgenonce(0, 0, -1000, 7, 0, 100, .1, 150, 1, 250, .3, 300, .7, 200, 0)
	iWidow2 = ftgenonce(0, 0, -1000, 7, .2, 300, 1, 200, .3, 100, .7, 300, .1, 100, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_wills_widow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.03 * iDurRand), SchannelName, (1000 * iFreqScale), (800 * iFreqScale), .1, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.27 * iDurRand), (.2 * iDurRand), SchannelName, (1000 * iFreqScale), (1000 * iFreqScale), .2, iWidow1, giAvesAmp)
		schedulek("_Aves_osc", (.51 * iDurRand), (.29 * iDurRand), SchannelName, (900 * iFreqScale), (1100 * iFreqScale), .2, iWidow2, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Blue gray gnatcatcher (Polioptila caerulea)
; https://en.wikipedia.org/wiki/Blue-gray_gnatcatcher
; Habitat: open deciduous woods, shrubland
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_blue_gray_gnatcatcher, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iGnat1 = ftgenonce(0, 0, -1000, 7, 0, 150, 1, 600, .8, 150, 1, 100, .7)
	iGnat2 = ftgenonce(0, 0, -1000, 7, 0, 250, 1, 500, .7, 250, 0)
	
	; Create partial harmonic amp ftables
	iGnatHarm1 = ftgenonce(0, 0, -3, 2, .4, 1, .1)
	iGnatHarm2 = ftgenonce(0, 0, -3, 2, .4, 1, .2)
	iGnatHarm3 = ftgenonce(0, 0, -3, 2, .4, 1, .3)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_blue_gray_gnatcatcher-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.2 * iDurRand), SchannelName, (4000 * iFreqScale), (1000 * iFreqScale), .2, iGnat1, giAvesAmp, iGnatHarm1)
		schedulek("_Aves_oscbank", (.3 * iDurRand), (.13 * iDurRand), SchannelName, (4000 * iFreqScale), (800 * iFreqScale), .2, iGnat2, giAvesAmp, iGnatHarm2)
		schedulek("_Aves_oscbank", (.9 * iDurRand), (.25 * iDurRand), SchannelName, (4000 * iFreqScale), (800 * iFreqScale), .2, iGnat2, giAvesAmp, iGnatHarm3)
		schedulek("_Aves_oscbank", (1.3 * iDurRand), (.17 * iDurRand), SchannelName, (4000 * iFreqScale), (900 * iFreqScale), .2, iGnat1, giAvesAmp, iGnatHarm3)
		schedulek("_Aves_oscbank", (1.5 * iDurRand), (.17 * iDurRand), SchannelName, (4000 * iFreqScale), (700 * iFreqScale), .2, iGnat1, giAvesAmp, iGnatHarm3)
		schedulek("_Aves_oscbank", (1.7 * iDurRand), (.17 * iDurRand), SchannelName, (4000 * iFreqScale), (800 * iFreqScale), .2, iGnat2, giAvesAmp, iGnatHarm3)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Black-throated sparrow (Amphispiza bilineata)
; https://en.wikipedia.org/wiki/Black-throated_sparrow
; Habitat: arid desert hillsides, scrubland
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_black_throated_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iBlack1 = ftgenonce(0, 0, -1000, 7, 0, 30, .7, 30, 0, 30, .75, 30, 0, 30, \
		.8, 30, .05, 30, .85, 30, .1, 30, .9, 30, .1, 30, 1, 30, .1, 30, 1, 30, \
		.1, 30, 1, 30, .1, 30, 1, 30, .1, 30, 1, 30, .1, 30, 1, 30, .1, 30, 1, \
		30, .1, 30, 1, 30, .1, 30, 1, 30, .1, 30, 1, 30, 0, 30, .95, 30, 0, 40, .9)
	iBlack2 = ftgenonce(0, 0, -1000, 7, 0, 500, 1, 500, .2)
	iBlackAmp1 = ftgenonce(0, 0, -1000, 7, 0, 50, 1, 950, 0)
	iBlackAmp2 = ftgenonce(0, 0, -1000, 7, 0, 750, 1, 250, 0)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_black_throated_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.02 * iDurRand), SchannelName, (2200 * iFreqScale), (1000 * iFreqScale), .1, giAvesRampDown, giAvesAmp)
		schedulek("_Aves_osc", (.03 * iDurRand), (.01 * iDurRand), SchannelName, (3000 * iFreqScale), (200 * iFreqScale), .05, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.16 * iDurRand), (.02 * iDurRand), SchannelName, (5800 * iFreqScale), (500 * iFreqScale), .05, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.2 * iDurRand), (.02 * iDurRand), SchannelName, (4000 * iFreqScale), (200 * iFreqScale), .05, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.24 * iDurRand), (.1 * iDurRand), SchannelName, (2100 * iFreqScale), (1600 * iFreqScale), .15, giAvesRampDown, iBlackAmp2)
		schedulek("_Aves_osc", (.35 * iDurRand), (.05 * iDurRand), SchannelName, (5700 * iFreqScale), (400 * iFreqScale), .25, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.45 * iDurRand), (.25 * iDurRand), SchannelName, (2000 * iFreqScale), (900 * iFreqScale), .2, iBlack1, giAvesAmp)
		schedulek("_Aves_osc", (.72 * iDurRand), (.05 * iDurRand), SchannelName, (5600 * iFreqScale), (400 * iFreqScale), .15, iBlack2, giAvesAmp)
		schedulek("_Aves_osc", (.8 * iDurRand), (.04 * iDurRand), SchannelName, (3900 * iFreqScale), (1100 * iFreqScale), .15, giAvesRampUp, giAvesAmp)
		schedulek("_Aves_osc", (.86 * iDurRand), (.01 * iDurRand), SchannelName, (1900 * iFreqScale), (100 * iFreqScale), .1, giAvesRampUp, iBlackAmp1)

		kIndex = 0
		while (kIndex <5) do
			schedulek("_Aves_osc", ((.89 + .9 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (3600 * iFreqScale), (300 * iFreqScale), .1, giAvesRampUp, iBlackAmp1)
			schedulek("_Aves_osc", ((.91 + .9 * kIndex) * iDurRand), (.03 * iDurRand), SchannelName, (3900 * iFreqScale), (1000 * iFreqScale), .15, giAvesRampUp, iBlackAmp1)
			schedulek("_Aves_osc", ((.94 + .9 * kIndex) * iDurRand), (.02 * iDurRand), SchannelName, (5000 * iFreqScale), (100 * iFreqScale), .2, giAvesRampUp, iBlackAmp1)
			schedulek("_Aves_osc", ((.96 + .9 * kIndex) * iDurRand), (.01 * iDurRand), SchannelName, (1900 * iFreqScale), (100 * iFreqScale), .1, giAvesRampUp, iBlackAmp1)
			kIndex += 1
		od

		schedulek("_Aves_osc", (1.36 * iDurRand), (.03 * iDurRand), SchannelName, (3800 * iFreqScale), (300 * iFreqScale), .1, giAvesRampUp, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Black-chinned sparrow (Spizella atrogularis)
; https://en.wikipedia.org/wiki/Black-chinned_sparrow
; Habitat: pine-juniper woodlands, other shrubland
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_black_chinned_sparrow, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iChinUp1 = giAvesRampUp
	iChinUp2 = ftgenonce(0, 0, -1000, 7, 0, 300, .2, 700, 1)
	
	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_black_chinned_sparrow-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_osc", 0, (.2 * iDurRand), SchannelName, (4200 * iFreqScale), (1000 * iFreqScale), .1, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (.4 * iDurRand), (.09 * iDurRand), SchannelName, (3800 * iFreqScale), (2000 * iFreqScale), .1, iChinUp2, giAvesAmp)
		schedulek("_Aves_osc", (.65 * iDurRand), (.08 * iDurRand), SchannelName, (3900 * iFreqScale), (1700 * iFreqScale), .12, iChinUp2, giAvesAmp)
		schedulek("_Aves_osc", (.8 * iDurRand), (.08 * iDurRand), SchannelName, (3600 * iFreqScale), (2300 * iFreqScale), .13, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (.9 * iDurRand), (.11 * iDurRand), SchannelName, (3100 * iFreqScale), (2800 * iFreqScale), .14, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.05 * iDurRand), (.07 * iDurRand), SchannelName, (2900 * iFreqScale), (2700 * iFreqScale), .15, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.14 * iDurRand), (.07 * iDurRand), SchannelName, (2900 * iFreqScale), (2700 * iFreqScale), .15, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.22 * iDurRand), (.07 * iDurRand), SchannelName, (3000 * iFreqScale), (2300 * iFreqScale), .13, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.29 * iDurRand), (.07 * iDurRand), SchannelName, (3200 * iFreqScale), (2000 * iFreqScale), .1, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.37 * iDurRand), (.05 * iDurRand), SchannelName, (3200 * iFreqScale), (1500 * iFreqScale), .1, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.44 * iDurRand), (.04 * iDurRand), SchannelName, (3400 * iFreqScale), (1000 * iFreqScale), .07, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.5 * iDurRand), (.03 * iDurRand), SchannelName, (3600 * iFreqScale), (700 * iFreqScale), .05, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.55 * iDurRand), (.03 * iDurRand), SchannelName, (3800 * iFreqScale), (300 * iFreqScale), .05, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.59 * iDurRand), (.02 * iDurRand), SchannelName, (3900 * iFreqScale), (100 * iFreqScale), .03, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.62 * iDurRand), (.01 * iDurRand), SchannelName, (3900 * iFreqScale), (100 * iFreqScale), .01, iChinUp1, giAvesAmp)
		schedulek("_Aves_osc", (1.64 * iDurRand), (.01 * iDurRand), SchannelName, (3900 * iFreqScale), (100 * iFreqScale), .01, iChinUp1, giAvesAmp)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

; Gull colony
; iAge - simple age/size parameter between 0 and 1, where 0 is young/small
; (default: 1)
; kTrig - Optional trigger for the bird call, if omitted the call will be
; triggered once
opcode m_aves_gull_colony, a, pJ
	iAge, kTrig xin

	; Create an internal trigger
	if (kTrig == -1) then
		kPlay init 1
	else
		kPlay = kTrig
	endif

	; Translate age to a frequency factor
	iFreqScale init linlin:i(iAge, 1.5, 1)

	; duration randomness
	iDurRand init (1 - rnd31(.01, 0))

	; specific envelopes
	iGullStart = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 100, .5, 200, .6, 200, .5, 400, 0)
	iGullEnd = ftgenonce(0, 0, -1000, 7, 0, 50, 1, 50, .5, 800, .4, 100, 0)
	iGull1 = ftgenonce(0, 0, -1000, 7, 0, 100, 1, 200, .5, 500, .5, 200, 0)
	
	; Create partial harmonic amp ftables
	iGullHarm = ftgenonce(0, 0, -7, 2, .1, 1, .1, .01, .09, .01, .01)

	; Create the channel name for this bird
	iUniqueID = rnd31(32768, 0) + 32768
	SchannelName = strcat("m_aves_gull_colony-", sprintf("%f", iUniqueID))
	chn_a(SchannelName, 3)

	; Schedule the audio generating instruments
	if (kPlay == 1) then
		schedulek("_Aves_oscbank", 0, (.8 * iDurRand), SchannelName, (1180 * iFreqScale), (1180 * iFreqScale), .08, iGullEnd, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (1.25 * iDurRand), (.9 * iDurRand), SchannelName, (1180 * iFreqScale), (1180 * iFreqScale), .07, iGullEnd, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (2.5 * iDurRand), (1.0 * iDurRand), SchannelName, (1050 * iFreqScale), (1050 * iFreqScale), .08, iGullEnd, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (4.55 * iDurRand), (.05 * iDurRand), SchannelName, (1180 * iFreqScale), (1180 * iFreqScale), .06, iGullStart, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (4.7 * iDurRand), (.1 * iDurRand), SchannelName, (1180 * iFreqScale), (1180 * iFreqScale), .08, iGullStart, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (4.9 * iDurRand), (.1 * iDurRand), SchannelName, (1180 * iFreqScale), (1180 * iFreqScale), .09, iGullStart, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (5.1 * iDurRand), (.1 * iDurRand), SchannelName, (1180 * iFreqScale), (1180 * iFreqScale), .1, iGull1, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (5.2 * iDurRand), (.4 * iDurRand), SchannelName, (1050 * iFreqScale), (1050 * iFreqScale), .1, iGullEnd, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (6.0 * iDurRand), (.8 * iDurRand), SchannelName, (1050 * iFreqScale), (1050 * iFreqScale), .1, iGullEnd, giAvesAmp, iGullHarm)
		schedulek("_Aves_oscbank", (7.2 * iDurRand), (1.8 * iDurRand), SchannelName, (1050 * iFreqScale), (1050 * iFreqScale), .1, iGullEnd, giAvesAmp, iGullHarm)
	endif

	; Read and output the audio
	aOut = chnget:a(SchannelName)
	chnclear(SchannelName)
	xout(aOut)
	kPlay = 0
endop

instr Play_birds
	kKlick init 1
	aOut[] init 40
	kTrig[] init 40
	kTrig[1] = kKlick
	kTrig[0] = delayk(kKlick, 3)
	kTrig[2] = delayk(kKlick, 6)
	kTrig[3] = delayk(kKlick, 9)
	kTrig[4] = delayk(kKlick, 12)
	kTrig[5] = delayk(kKlick, 15)
	kTrig[6] = delayk(kKlick, 18)
	kTrig[7] = delayk(kKlick, 21)
	kTrig[8] = delayk(kKlick, 24)
	kTrig[9] = delayk(kKlick, 27)
	kTrig[10] = delayk(kKlick, 30)
	kTrig[11] = delayk(kKlick, 33)
	kTrig[12] = delayk(kKlick, 36)
	kTrig[13] = delayk(kKlick, 39)
	kTrig[14] = delayk(kKlick, 42)
	kTrig[15] = delayk(kKlick, 45)
	kTrig[16] = delayk(kKlick, 48)
	kTrig[17] = delayk(kKlick, 51)
	kTrig[18] = delayk(kKlick, 54)
	kTrig[19] = delayk(kKlick, 57)
	kTrig[20] = delayk(kKlick, 61)
	kTrig[21] = delayk(kKlick, 64)
	kTrig[22] = delayk(kKlick, 67)
	kTrig[23] = delayk(kKlick, 70)
	kTrig[24] = delayk(kKlick, 73)
	kTrig[25] = delayk(kKlick, 76)
	kTrig[26] = delayk(kKlick, 79)
	kTrig[27] = delayk(kKlick, 82)
	kTrig[28] = delayk(kKlick, 85)
	kTrig[29] = delayk(kKlick, 88)
	kTrig[30] = delayk(kKlick, 91)
	kTrig[31] = delayk(kKlick, 94)
	kTrig[32] = delayk(kKlick, 97)
	kTrig[33] = delayk(kKlick, 100)
	kTrig[34] = delayk(kKlick, 103)
	kTrig[35] = delayk(kKlick, 106)
	kTrig[36] = delayk(kKlick, 109)
	kTrig[37] = delayk(kKlick, 112)
	kTrig[38] = delayk(kKlick, 115)
	kTrig[39] = delayk(kKlick, 118)

	aOut[0] = m_aves_cassins_kingbird(1, kTrig[0])
	aOut[1] = m_aves_orchard_oriole(1, kTrig[1])
	aOut[2] = m_aves_chipping_sparrow(1, kTrig[2])
	aOut[3] = m_aves_bobwhite(1, kTrig[3])
	aOut[4] = m_aves_meadowlark(1, kTrig[4])
	aOut[5] = m_aves_scissor_flycatcher(1, kTrig[5])
	aOut[6] = m_aves_great_horned_owl(1, kTrig[6])
	aOut[7] = m_aves_gray_warbler(1, kTrig[7])
	aOut[8] = m_aves_yellow_warbler(1, kTrig[8])
	aOut[9] = m_aves_black_stilt(1, kTrig[9])
	aOut[10] = m_aves_chestnut_warbler(1, kTrig[10])
	aOut[11] = m_aves_grasshopper_sparrow(1, kTrig[11])
	aOut[12] = m_aves_swamp_sparrow(1, kTrig[12])
	aOut[13] = m_aves_golden_sparrow(1, kTrig[13])
	aOut[14] = m_aves_indigo_bunting(1, kTrig[14])
	aOut[15] = m_aves_hooded_warbler(1, kTrig[15])
	aOut[16] = m_aves_american_widgeon(1, kTrig[16])
	aOut[17] = m_aves_louisiana_waterthrush(1, kTrig[17])
	aOut[18] = m_aves_robin(1, kTrig[18])
	aOut[19] = m_aves_solitary_vireo(1, kTrig[19])
	aOut[20] = m_aves_pigeon_hawk(1, kTrig[20])
	aOut[21] = m_aves_cerulean_warbler(1, kTrig[21])
	aOut[22] = m_aves_nashville_warbler(1, kTrig[22])
	aOut[23] = m_aves_eastern_phoebe(1, kTrig[23])
	aOut[24] = m_aves_painted_bunting(1, kTrig[24])
	aOut[25] = m_aves_western_flycatcher(1, kTrig[25])
	aOut[26] = m_aves_bachmans_sparrow(1, kTrig[26])
	aOut[27] = m_aves_cedar_waxwing(1, kTrig[27])
	aOut[28] = m_aves_bairds_sparrow(1, kTrig[28])
	aOut[29] = m_aves_kentucky_warbler(1, kTrig[29])
	aOut[30] = m_aves_rufous_towhee(1, kTrig[30])
	aOut[31] = m_aves_prothonotary(1, kTrig[31])
	aOut[32] = m_aves_audubons_warbler(1, kTrig[32])
	aOut[33] = m_aves_lark_bunting(1, kTrig[33])
	aOut[34] = m_aves_eastern_bluebird(1, kTrig[34])
	aOut[35] = m_aves_wills_widow(1, kTrig[35])
	aOut[36] = m_aves_blue_gray_gnatcatcher(1, kTrig[36])
	aOut[37] = m_aves_black_throated_sparrow(1, kTrig[37])
	aOut[38] = m_aves_black_chinned_sparrow(1, kTrig[38])
	aOut[39] = m_aves_gull_colony(1, kTrig[39])

	; Sum the output and play
	aPlay = aOut[0] + aOut[1] + aOut[2] + aOut[3] + aOut[4] + aOut[5] + aOut[6] \
		+ aOut[7] + aOut[8] + aOut[9] + aOut[10] + aOut[11] + aOut[12] + aOut[13] \
		+ aOut[14] + aOut[15] + aOut[16] + aOut[17] + aOut[18] + aOut[19] \
		+ aOut[20] + aOut[21] + aOut[22] + aOut[23] + aOut[24] + aOut[25] \
		+ aOut[26] + aOut[27] + aOut[28] + aOut[29] + aOut[30] + aOut[31] \
		+ aOut[32] + aOut[33] + aOut[34] + aOut[35] + aOut[36] + aOut[37] \
		+ aOut[38] + aOut[39]
	outs(aPlay, aPlay)
	kKlick = 0
endin

#endif
