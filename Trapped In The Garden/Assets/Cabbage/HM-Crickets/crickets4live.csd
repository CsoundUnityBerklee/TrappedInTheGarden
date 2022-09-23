<CsoundSynthesizer>
<CsInstruments>
;---------------------------------------------------------

; CRICKETS

; CODED BY HANS MIKELSON SEPTEMBER, 1999

;---------------------------------------------------------

sr	= 44100
kr	= 441
ksmps	= 100
nchnls = 2 

;---------------------------------------------------------

; CRICKET 2

;---------------------------------------------------------

               instr          14
 

idur           =              p3                  ; DURATION

iamp           =              p4                  ; AMPLITUDE

ifqc           =              p5                  ; FREQUENCY MODIFICATION

ipuls          =              p6                  ; PULSE TABLE

iftab          =              p7                  ; FREQUENCY TABLE

iloop          =              p8                  ; LOOP TIME

iltab          =              p9                  ; LOOP TABLE

ilpetab        =              p10                 ; LOOP ENVELOPE TABLE

ifetab         =              p11                 ; FREQUENCY ENVELOPE TABLE

ibasef         =              19                  ; BASE PULSE FREQUENCY

ipanl          =              sqrt(p12)           ; PAN LEFT

ipanr          =              sqrt(1-p12)         ; PAN RIGHT

iv             =              iamp/10000          ; HIGH SHELF LEVEL
 

kaf            oscili         2, 1/iloop, iltab        ; PULSE ENVELOPE FM

kamp1          oscili         1, 1/iloop, ilpetab      ; LOOP ENVELOPE

kfenv          oscili         1, 1/iloop, ifetab       ; LOOP FREQUENCY ENVELOPE

     

kamp2          oscili         1, ibasef*kaf, ipuls     ; GENERATE PULSE STREAM

kamp           =              sqrt(kamp1*kamp2)        ; MAKE IT ROUNDED
 

kfqc1          oscil          4800*kfenv*ifqc, ibasef*kaf, iftab      ; FUNDAMENTAL FQC

kfqc2          oscil          9500*kfenv*ifqc, ibasef*kaf, iftab      ; OVERTONE
 

kdclck         linseg         0, .005, 1, idur-.01, 1, .005, 0        ; DECLICK ENVELOPE
 

afnd           oscil          kamp, kfqc1, 1                          ; FUNDAMENTAL OSCILLATOR

ahrm           oscil          kamp, kfqc2, 1                          ; OVERTONE OSCILLATOR
 

aout           pareq          (afnd+ahrm*.04)*iamp*kdclck, 7000, iv, .707, 2    ; SET HIGH SHELF FILTER LOW FOR DISTANT CRICKETS
 

               outs           aout*ipanl, aout*ipanr                  ; OUTPUT THE SOUND WITH PANNING
 

               endin
 

</CsInstruments>
<CsScore>
; SCO

f1 0 65536 10 1

f2 0 1024  7  0 306 1   306 0   412 0

f3 0 1024  7  1 153 .97 153 .92 306 .85 412 1

f4 0 1024  7  1  43 1    10  .5  961 .5 10 1

f5 0 1024  7  .5 43 .5   10  .8  240 1 10 0 721 0 10 .5     ; LOOP ENVELOPE

f8 0 1024  7  .5 43 .5   10  .8  300 1 10 0 661 0 10 .5     ; LOOP ENVELOPE

f6 0 1024  7  .9 43 .9   10  1   961 1 10  .9

f7 0 1024  7  1 1024 1
 

; CRICKET

;    Sta  Dur   Amp    Fqc  PlsTab  FqcTab  Loop  LoopFM   LoopEnv  FqcEnv Pan

 
i14  0 30   3200   .858  2       3       .5    4        8        6     .9 

i14 0.75 30     5300   1.05 2       3       .6    4        8        6     .8
e
i14  1.5 30    3500   .992 2       3       .6    4        5        6     .6


</CsScore>

</CsoundSynthesizer>
