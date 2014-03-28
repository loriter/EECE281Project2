;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1034 (Dec 12 2012) (MSVC)
; This file was generated Thu Mar 27 14:26:06 2014
;--------------------------------------------------------
$name Transmitter
$optc51 --model-small
	R_DSEG    segment data
	R_CSEG    segment code
	R_BSEG    segment bit
	R_XSEG    segment xdata
	R_PSEG    segment xdata
	R_ISEG    segment idata
	R_OSEG    segment data overlay
	BIT_BANK  segment data overlay
	R_HOME    segment code
	R_GSINIT  segment code
	R_IXSEG   segment xdata
	R_CONST   segment code
	R_XINIT   segment code
	R_DINIT   segment code

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	public _main
	public _wave_freq
	public _sendCommand
	public _waitBitTime
	public __c51_external_startup
;--------------------------------------------------------
; Special Function Registers
;--------------------------------------------------------
_ACC            DATA 0xe0
_B              DATA 0xf0
_PSW            DATA 0xd0
_SP             DATA 0x81
_SPX            DATA 0xef
_DPL            DATA 0x82
_DPH            DATA 0x83
_DPLB           DATA 0xd4
_DPHB           DATA 0xd5
_PAGE           DATA 0xf6
_AX             DATA 0xe1
_BX             DATA 0xf7
_DSPR           DATA 0xe2
_FIRD           DATA 0xe3
_MACL           DATA 0xe4
_MACH           DATA 0xe5
_PCON           DATA 0x87
_AUXR           DATA 0x8e
_AUXR1          DATA 0xa2
_DPCF           DATA 0xa1
_CKRL           DATA 0x97
_CKCKON0        DATA 0x8f
_CKCKON1        DATA 0xaf
_CKSEL          DATA 0x85
_CLKREG         DATA 0xae
_OSCCON         DATA 0x85
_IE             DATA 0xa8
_IEN0           DATA 0xa8
_IEN1           DATA 0xb1
_IPH0           DATA 0xb7
_IP             DATA 0xb8
_IPL0           DATA 0xb8
_IPH1           DATA 0xb3
_IPL1           DATA 0xb2
_P0             DATA 0x80
_P1             DATA 0x90
_P2             DATA 0xa0
_P3             DATA 0xb0
_P4             DATA 0xc0
_P0M0           DATA 0xe6
_P0M1           DATA 0xe7
_P1M0           DATA 0xd6
_P1M1           DATA 0xd7
_P2M0           DATA 0xce
_P2M1           DATA 0xcf
_P3M0           DATA 0xc6
_P3M1           DATA 0xc7
_P4M0           DATA 0xbe
_P4M1           DATA 0xbf
_SCON           DATA 0x98
_SBUF           DATA 0x99
_SADEN          DATA 0xb9
_SADDR          DATA 0xa9
_BDRCON         DATA 0x9b
_BRL            DATA 0x9a
_TCON           DATA 0x88
_TMOD           DATA 0x89
_TCONB          DATA 0x91
_TL0            DATA 0x8a
_TH0            DATA 0x8c
_TL1            DATA 0x8b
_TH1            DATA 0x8d
_RL0            DATA 0xf2
_RH0            DATA 0xf4
_RL1            DATA 0xf3
_RH1            DATA 0xf5
_WDTRST         DATA 0xa6
_WDTPRG         DATA 0xa7
_T2CON          DATA 0xc8
_T2MOD          DATA 0xc9
_RCAP2H         DATA 0xcb
_RCAP2L         DATA 0xca
_TH2            DATA 0xcd
_TL2            DATA 0xcc
_SPCON          DATA 0xc3
_SPSTA          DATA 0xc4
_SPDAT          DATA 0xc5
_SSCON          DATA 0x93
_SSCS           DATA 0x94
_SSDAT          DATA 0x95
_SSADR          DATA 0x96
_KBLS           DATA 0x9c
_KBE            DATA 0x9d
_KBF            DATA 0x9e
_KBMOD          DATA 0x9f
_BMSEL          DATA 0x92
_FCON           DATA 0xd2
_EECON          DATA 0xd2
_ACSRA          DATA 0xa3
_ACSRB          DATA 0xab
_AREF           DATA 0xbd
_DADC           DATA 0xa4
_DADI           DATA 0xa5
_DADL           DATA 0xac
_DADH           DATA 0xad
_CCON           DATA 0xd8
_CMOD           DATA 0xd9
_CL             DATA 0xe9
_CH             DATA 0xf9
_CCAPM0         DATA 0xda
_CCAPM1         DATA 0xdb
_CCAPM2         DATA 0xdc
_CCAPM3         DATA 0xdd
_CCAPM4         DATA 0xde
_CCAP0H         DATA 0xfa
_CCAP1H         DATA 0xfb
_CCAP2H         DATA 0xfc
_CCAP3H         DATA 0xfd
_CCAP4H         DATA 0xfe
_CCAP0L         DATA 0xea
_CCAP1L         DATA 0xeb
_CCAP2L         DATA 0xec
_CCAP3L         DATA 0xed
_CCAP4L         DATA 0xee
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
_ACC_0          BIT 0xe0
_ACC_1          BIT 0xe1
_ACC_2          BIT 0xe2
_ACC_3          BIT 0xe3
_ACC_4          BIT 0xe4
_ACC_5          BIT 0xe5
_ACC_6          BIT 0xe6
_ACC_7          BIT 0xe7
_B_0            BIT 0xf0
_B_1            BIT 0xf1
_B_2            BIT 0xf2
_B_3            BIT 0xf3
_B_4            BIT 0xf4
_B_5            BIT 0xf5
_B_6            BIT 0xf6
_B_7            BIT 0xf7
_P              BIT 0xd0
_F1             BIT 0xd1
_OV             BIT 0xd2
_RS0            BIT 0xd3
_RS1            BIT 0xd4
_F0             BIT 0xd5
_AC             BIT 0xd6
_CY             BIT 0xd7
_EX0            BIT 0xa8
_ET0            BIT 0xa9
_EX1            BIT 0xaa
_ET1            BIT 0xab
_ES             BIT 0xac
_ET2            BIT 0xad
_EC             BIT 0xae
_EA             BIT 0xaf
_PX0            BIT 0xb8
_PT0            BIT 0xb9
_PX1            BIT 0xba
_PT1            BIT 0xbb
_PS             BIT 0xbc
_PT2            BIT 0xbd
_IP0D           BIT 0xbf
_PPCL           BIT 0xbe
_PT2L           BIT 0xbd
_PLS            BIT 0xbc
_PT1L           BIT 0xbb
_PX1L           BIT 0xba
_PT0L           BIT 0xb9
_PX0L           BIT 0xb8
_P0_0           BIT 0x80
_P0_1           BIT 0x81
_P0_2           BIT 0x82
_P0_3           BIT 0x83
_P0_4           BIT 0x84
_P0_5           BIT 0x85
_P0_6           BIT 0x86
_P0_7           BIT 0x87
_P1_0           BIT 0x90
_P1_1           BIT 0x91
_P1_2           BIT 0x92
_P1_3           BIT 0x93
_P1_4           BIT 0x94
_P1_5           BIT 0x95
_P1_6           BIT 0x96
_P1_7           BIT 0x97
_P2_0           BIT 0xa0
_P2_1           BIT 0xa1
_P2_2           BIT 0xa2
_P2_3           BIT 0xa3
_P2_4           BIT 0xa4
_P2_5           BIT 0xa5
_P2_6           BIT 0xa6
_P2_7           BIT 0xa7
_P3_0           BIT 0xb0
_P3_1           BIT 0xb1
_P3_2           BIT 0xb2
_P3_3           BIT 0xb3
_P3_4           BIT 0xb4
_P3_5           BIT 0xb5
_P3_6           BIT 0xb6
_P3_7           BIT 0xb7
_RXD            BIT 0xb0
_TXD            BIT 0xb1
_INT0           BIT 0xb2
_INT1           BIT 0xb3
_T0             BIT 0xb4
_T1             BIT 0xb5
_WR             BIT 0xb6
_RD             BIT 0xb7
_P4_0           BIT 0xc0
_P4_1           BIT 0xc1
_P4_2           BIT 0xc2
_P4_3           BIT 0xc3
_P4_4           BIT 0xc4
_P4_5           BIT 0xc5
_P4_6           BIT 0xc6
_P4_7           BIT 0xc7
_RI             BIT 0x98
_TI             BIT 0x99
_RB8            BIT 0x9a
_TB8            BIT 0x9b
_REN            BIT 0x9c
_SM2            BIT 0x9d
_SM1            BIT 0x9e
_SM0            BIT 0x9f
_IT0            BIT 0x88
_IE0            BIT 0x89
_IT1            BIT 0x8a
_IE1            BIT 0x8b
_TR0            BIT 0x8c
_TF0            BIT 0x8d
_TR1            BIT 0x8e
_TF1            BIT 0x8f
_CP_RL2         BIT 0xc8
_C_T2           BIT 0xc9
_TR2            BIT 0xca
_EXEN2          BIT 0xcb
_TCLK           BIT 0xcc
_RCLK           BIT 0xcd
_EXF2           BIT 0xce
_TF2            BIT 0xcf
_CF             BIT 0xdf
_CR             BIT 0xde
_CCF4           BIT 0xdc
_CCF3           BIT 0xdb
_CCF2           BIT 0xda
_CCF1           BIT 0xd9
_CCF0           BIT 0xd8
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	rbank0 segment data overlay
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	rseg R_DSEG
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg R_OSEG
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	rseg R_ISEG
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	DSEG
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	rseg R_BSEG
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	rseg R_PSEG
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	rseg R_XSEG
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	XSEG
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	rseg R_IXSEG
	rseg R_HOME
	rseg R_GSINIT
	rseg R_CSEG
;--------------------------------------------------------
; Reset entry point and interrupt vectors
;--------------------------------------------------------
	CSEG at 0x0000
	ljmp	_crt0
	CSEG at 0x000b
	ljmp	_wave_freq
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	rseg R_HOME
	rseg R_GSINIT
	rseg R_GSINIT
;--------------------------------------------------------
; data variables initialization
;--------------------------------------------------------
	rseg R_DINIT
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function '_c51_external_startup'
;------------------------------------------------------------
;------------------------------------------------------------
;	Z:\GHRepos\EECE281Project2\Transmitter.c:12: unsigned char _c51_external_startup(void)
;	-----------------------------------------
;	 function _c51_external_startup
;	-----------------------------------------
__c51_external_startup:
	using	0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:15: P0M0=0;	P0M1=0;
	mov	_P0M0,#0x00
	mov	_P0M1,#0x00
;	Z:\GHRepos\EECE281Project2\Transmitter.c:16: P1M0=0;	P1M1=0;
	mov	_P1M0,#0x00
	mov	_P1M1,#0x00
;	Z:\GHRepos\EECE281Project2\Transmitter.c:17: P2M0=0;	P2M1=0;
	mov	_P2M0,#0x00
	mov	_P2M1,#0x00
;	Z:\GHRepos\EECE281Project2\Transmitter.c:18: P3M0=0;	P3M1=0;
	mov	_P3M0,#0x00
	mov	_P3M1,#0x00
;	Z:\GHRepos\EECE281Project2\Transmitter.c:19: AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
	mov	_AUXR,#0x11
;	Z:\GHRepos\EECE281Project2\Transmitter.c:20: P4M0=0;	P4M1=0;
	mov	_P4M0,#0x00
	mov	_P4M1,#0x00
;	Z:\GHRepos\EECE281Project2\Transmitter.c:23: PCON|=0x80;
	orl	_PCON,#0x80
;	Z:\GHRepos\EECE281Project2\Transmitter.c:24: SCON = 0x52;
	mov	_SCON,#0x52
;	Z:\GHRepos\EECE281Project2\Transmitter.c:25: BDRCON=0;
	mov	_BDRCON,#0x00
;	Z:\GHRepos\EECE281Project2\Transmitter.c:26: BRL=BRG_VAL;
	mov	_BRL,#0xFA
;	Z:\GHRepos\EECE281Project2\Transmitter.c:27: BDRCON=BRR|TBCK|RBCK|SPD;
	mov	_BDRCON,#0x1E
;	Z:\GHRepos\EECE281Project2\Transmitter.c:30: TR0=0; // Stop timer 0
	clr	_TR0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:31: TMOD=0x01; // 16-bit timer
	mov	_TMOD,#0x01
;	Z:\GHRepos\EECE281Project2\Transmitter.c:36: TH0=RH0=TIMER0_RELOAD_VALUE/0x100;
	mov	_RH0,#0xFF
	mov	_TH0,#0xFF
;	Z:\GHRepos\EECE281Project2\Transmitter.c:37: TL0=RL0=TIMER0_RELOAD_VALUE%0x100;
	mov	_RL0,#0xCA
	mov	_TL0,#0xCA
;	Z:\GHRepos\EECE281Project2\Transmitter.c:38: TR0=1; // Start timer 0 (bit 4 in TCON)
	setb	_TR0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:39: ET0=1; // Enable timer 0 interrupt
	setb	_ET0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:40: EA=1;  // Enable global interrupts
	setb	_EA
;	Z:\GHRepos\EECE281Project2\Transmitter.c:42: return 0;
	mov	dpl,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'waitBitTime'
;------------------------------------------------------------
;------------------------------------------------------------
;	Z:\GHRepos\EECE281Project2\Transmitter.c:46: void waitBitTime(void)
;	-----------------------------------------
;	 function waitBitTime
;	-----------------------------------------
_waitBitTime:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:49: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'sendCommand'
;------------------------------------------------------------
;val                       Allocated to registers r2 
;i                         Allocated to registers r3 
;------------------------------------------------------------
;	Z:\GHRepos\EECE281Project2\Transmitter.c:51: void sendCommand(unsigned char val)
;	-----------------------------------------
;	 function sendCommand
;	-----------------------------------------
_sendCommand:
	mov	r2,dpl
;	Z:\GHRepos\EECE281Project2\Transmitter.c:56: TR0=0;
	clr	_TR0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:57: waitBitTime();
	push	ar2
	lcall	_waitBitTime
	pop	ar2
;	Z:\GHRepos\EECE281Project2\Transmitter.c:58: for(i = 0; i < 7; i++)
	mov	r3,#0x00
L004004?:
	cjne	r3,#0x07,L004014?
L004014?:
	jnc	L004007?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:60: if(val&(0x01<<i))
	mov	b,r3
	inc	b
	mov	r4,#0x01
	mov	r5,#0x00
	sjmp	L004017?
L004016?:
	mov	a,r4
	add	a,r4
	mov	r4,a
	mov	a,r5
	rlc	a
	mov	r5,a
L004017?:
	djnz	b,L004016?
	mov	ar6,r2
	mov	r7,#0x00
	mov	a,r6
	anl	ar4,a
	mov	a,r7
	anl	ar5,a
	mov	a,r4
	orl	a,r5
	jz	L004002?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:63: TR0=1;
	setb	_TR0
	sjmp	L004003?
L004002?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:68: TR0=0;
	clr	_TR0
L004003?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:70: waitBitTime();
	push	ar2
	push	ar3
	lcall	_waitBitTime
	pop	ar3
	pop	ar2
;	Z:\GHRepos\EECE281Project2\Transmitter.c:58: for(i = 0; i < 7; i++)
	inc	r3
	sjmp	L004004?
L004007?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:73: TR0=1;
	setb	_TR0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:74: waitBitTime();
	lcall	_waitBitTime
;	Z:\GHRepos\EECE281Project2\Transmitter.c:75: waitBitTime();
	ljmp	_waitBitTime
;------------------------------------------------------------
;Allocation info for local variables in function 'wave_freq'
;------------------------------------------------------------
;------------------------------------------------------------
;	Z:\GHRepos\EECE281Project2\Transmitter.c:82: void wave_freq (void) interrupt 1
;	-----------------------------------------
;	 function wave_freq
;	-----------------------------------------
_wave_freq:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:84: if(P2_0==0)
	jb	_P2_0,L005002?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:86: P2_0=1;
	setb	_P2_0
;	Z:\GHRepos\EECE281Project2\Transmitter.c:87: P2_1=0;
	clr	_P2_1
	sjmp	L005004?
L005002?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:91: P2_1=1;
	setb	_P2_1
;	Z:\GHRepos\EECE281Project2\Transmitter.c:92: P2_0=0;
	clr	_P2_0
L005004?:
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;	eliminated unneeded push/pop acc
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;------------------------------------------------------------
;	Z:\GHRepos\EECE281Project2\Transmitter.c:98: void main (void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:100: while(1)
L006022?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:103: if(P2_2 == 1)
	jnb	_P2_2,L006005?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:105: while(P2_2 == 1);
L006001?:
	jb	_P2_2,L006001?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:106: sendCommand(0B00000001);
	mov	dpl,#0x01
	lcall	_sendCommand
L006005?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:108: if(P2_3 == 1)
	jnb	_P2_3,L006010?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:110: while(P2_3 == 1);
L006006?:
	jb	_P2_3,L006006?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:111: sendCommand(0B00000010);
	mov	dpl,#0x02
	lcall	_sendCommand
L006010?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:113: if(P2_4 == 1)
	jnb	_P2_4,L006015?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:115: while(P2_4 == 1);
L006011?:
	jb	_P2_4,L006011?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:116: sendCommand(0B00000011);
	mov	dpl,#0x03
	lcall	_sendCommand
L006015?:
;	Z:\GHRepos\EECE281Project2\Transmitter.c:118: if(P2_5 == 1)
	jnb	_P2_5,L006022?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:120: while(P2_5 == 1);
L006016?:
	jb	_P2_5,L006016?
;	Z:\GHRepos\EECE281Project2\Transmitter.c:121: sendCommand(0B00000101);
	mov	dpl,#0x05
	lcall	_sendCommand
	sjmp	L006022?
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST

	CSEG

end
