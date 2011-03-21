/****************************************************************
sh_7045.h
Copyright (c) Kosaka Lab CS TNCT

このインクルードファイルはH8/3048用ファイルを下敷きにして
2003年度研究生山下君，永山さんの協力でまとめたものである。
28 Jun 2006 h8-01.h  小坂 chkgetSCI1のタイミング修正
 4 Dec 2003 h8-01.h  小坂，山下，永山

【１】SCI ch1 関係
void initSCI1()
 SCI-ch1の初期化　38400baud, Ascnc, 8bit , NoParity, stop1

short int getCharSCI1()
 SCI-ch1から1byte入力コード。エラーがあると-2が戻る。
short int chkgetCharSCI1()
 SCI-ch1を検査し，受信データがあれば1byte入力コードが戻る。
 なければ-1が，失敗すると-2が戻る。
short int getIntSCI1(char prompt[])
 SCI-ch1からプロンプト付で，short intの値を受け取る。
 正負の10進数または16進数を受け付ける。16進数は0xで始まる

void putCharSCI1(char c)
 SCI-ch1に1バイト出力する。
void putStringSCI1(char *str)
 SCI-ch1に文字列を出力する。
void SCI1_printf(char *format,...)
  関数printfのSCI版
  軽量化のためエラー処理はないので桁数指定の場合は注意
  対応書式
  %d   : [int] integer with sign. '%d','%4d','%-4d', and '%04d' are available
  %ld  : explicit [long int]  '%ld','%9ld','%-9ld', and '%09ld' are available
  %u   : [unsigbed int] unsigned integer.
            '%u','%4u','%-4u', and '%04u' are available
  %lu  : explicit [unsigned long int]
            '%lu','%9lu','%-9lu', and '%09lu' are available
  %x   : [unsigned int] in Hex  '%x','%4x','%-4x', and '%04x' are available
  %lx  : explicit [unsigned long int] in Hex  
            '%lx','%8lx','%-8lx', and '%08lx' are available
  %o   : [unsigned int] in Oct  '%o','%4o','%-4o', and '%04o' are available
  %lo  : explicit [unsigned long int] in Oct  
            '%lo','%8lo','%-8lo', and '%08lo' are available
  %b   : [unsigned int] in Bin  '%b','%8b','%-8b', and '%08b' are available
  %lb  : explicit [unsigned long int] in Bin  
            '%lb','%8lb','%-8lb', and '%08lb' are available
  %c   : char
  %s   : string %20s %-20s are available

【２】マザーボード関係
void initLed()
 LEDの初期化
void turnOnLed(short int number)
 LEDの点灯　numberはLED番号で0または1を指定する
void turnOffLed(short int number)
 LEDの消灯　numberはLED番号で0または1を指定する

void initPushSW(void)
 押しボタンスイッチの初期化
short int getPushSW(void)
 押しボタンスイッチの取得。
 押しボタンスイッチの状況は第0と第2ビットに現れる。
short int checkPushSW(short int number)
 push sw 0,1の状態を調べる　number:0 or 1
 押されていたら1、そうでなかったら0を返す

void init4BitSW(void)
 4ビットスイッチの初期化
short int get4BitSW(void)
 4ビットスイッチの取得　ただしポートを読み込み，ビット反転のみ。
 4ビットスイッチの状況は第0-第3ビットに現れる。
short int check4BitSW(short int number)
 4bitsw 0,1,2,3の状態を調べる　number:0,1,2,or 3
 ONなら1、そうでなかったら0を返す

【３】タイミング割り込み
void initCMTInt(unsigned long int period,int ch,int intLebel)
 コンペアマッチタイマによるタイマ割り込みの初期化 
 割り込み間隔は引数peiodで単位はμsecである 
 0<period<1170104 なので最長1.170104secまで可能 
 チャンネルが２つあるのではchは0,1のどちらかを選ぶ 
 割り込みレベルintLebelは1～15にする 
void startCMT0(void)
 コンペアマッチタイマ0スタート
void stopCMT0(void)
 コンペアマッチタイマ0ストップ
void clearCMFlag0(void)
 コンペアマッチフラッグ0クリア (割り込みルーチン内で呼び出すこと)
void startCMT1(void)
 コンペアマッチタイマ1スタート
void stopCMT1(void)
 コンペアマッチタイマ1ストップ
void clearCMFlag1(void)
 コンペアマッチフラッグ1クリア (割り込みルーチン内で呼び出すこと)

****************************************************************/
#include"7040S.h"
#include<stdarg.h>
void setIntMask(int mask);
int getIntMask(void);

/* ------------------------------------------------- */
/* SCI1 INITIALIZATION fixed baud at 38400           */
/* ------------------------------------------------- */
void initSCI1()
{
	int i;
	PFC.PACRL2.BIT.PA4MD = 1;/* 0:PA4, 1:TXD1 */
	PFC.PACRL2.BIT.PA3MD = 1;/* 0:PA3, 1:RXD1 */
	SCI1.SCR.BYTE = 0;       /* clear all flags */
	SCI1.SCR.BYTE = 0;       /* clear all flags */
	                  /* 2400-38400baud are available at n=0(cks1=0,cks2=0) */
	SCI1.SMR.BYTE = 0;       /* Ascnc, 8bit , NoParity, stop1, 1/1 */
	SCI1.BRR = 22;	         /* 38400baud (CPU=28.6MHz) */
	for(i=0;i<1000000;i++);      /* wait more than 1bit time */
	SCI1.SCR.BYTE = 0x30;    /* scr = 0011 0000 (TE=1,RE=1) */
	return;
}

/* ------------------------------------------------- */
/* GET BYTE FROM SCI1 */
/* ------------------------------------------------- */
short int getCharSCI1()
/* return value 0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	do {
		flags = SCI1.SSR.BYTE;
		if (flags&0x38) {/* error */
			SCI1.SSR.BIT.RDRF = 0;
			SCI1.SSR.BIT.ORER = 0;
			SCI1.SSR.BIT.FER = 0;
			SCI1.SSR.BIT.PER = 0;
			return -2;
		}
		if (flags&0x40) {/* normally received one data */
			SCI1.SSR.BIT.RDRF = 0;
			recdata=SCI1.RDR;
			return recdata;
		}
	} while (1);
}

/* ------------------------------------------------- */
/* CHECK SCI BUFFER AND GET DATA */
/* ------------------------------------------------- */
short int chkgetCharSCI1()
/* return value -1(0xFFFF):no received data  */
/*              0x00-0xFF:received data */
/*              -2(0xFFFE):error */
{
	short int flags,recdata;
	flags = SCI1.SSR.BYTE;
	if (flags&0x38) {/* error */
		SCI1.SSR.BIT.RDRF = 0;
		SCI1.SSR.BIT.ORER = 0;
		SCI1.SSR.BIT.FER = 0;
		SCI1.SSR.BIT.PER = 0;
		return -2;
	}
	if (flags&0x40) {/* normally received one data */
		recdata=SCI1.RDR;
		SCI1.SSR.BIT.RDRF = 0;
		return recdata;
	} else {
		return -1;
	}
}

void putStringSCI1(char *str);

/*SCI1より文字列入力[return]が終端だが，'\n'は取得されない*/
/*^Hでバックスペイス*/
int getStringSCI1(char *buff,int max)
{
	int i,ch;
	for (i=0;i<max-1;i++) {
		ch=getCharSCI1(); /*1文字取得*/
		*buff=(char)ch; /*1文字取得*/
		if (*buff=='\r'||ch<0) {
			*buff=0;
			return i+1;
		}
		if (*buff==0x8) {
			buff-=2;
			i-=2;
		}
		if (*buff!='\n') buff++;
		else i--;
	}
	*buff=0;
	return i+1;
}

/*SCI1へプロンプトを表示して，SCI1より整数値を入力*/
int getIntSCI1(char prompt[])
/*getting integer from serial port*/
/* format 123[ret] */
/*        -123[ret] */
/*        0x1a[ret] */
/*        -0x100[ret] */
{
	int x=0,y,m=0,n=0,v=0,i=0;
	char buff[16];
	putStringSCI1(prompt);
	getStringSCI1(buff,16);
	y=buff[i];
	while(y!=0){
		if(y=='-') m=1;
		if('a'<=y&&y<='z') y=y-'a'+'A';
		if(y=='0') n=1;

		if(v==1){
			if('0'<=y&&y<='9'){
				y=y-'0';
			}
			else if('A'<=y&&y<='F'){
				y=y-'A'+10;
			}
			x=16*x+y;
		}

		if(n==1&&y=='X'){
			v=1;
		}
				
		if(v==0&&'0'<=y&&y<='9'){
			y=y-'0';
			x=10*x+y;
		}

		y=buff[++i];
	}
	if(m==1) x=-x;
	return x;
}

/* ------------------------------------------------- */
/* PUT BYTE TO SCI1 */
/* ------------------------------------------------- */
void putCharSCI1(char c)
{
	unsigned char tmp;
	if (c=='\n') putCharSCI1('\r');
	do{
		tmp = SCI1.SSR.BYTE;
	} while((tmp & 0x80)==0);
	SCI1.TDR = c;
	SCI1.SSR.BIT.TDRE = 0;
	return;
}

void putStringSCI1(char *str)
{
	while(*str){
		putCharSCI1(*str);
		str++;
	}
}

const char hexstring[]="0123456789abcdef0123456789ABCDEF";
#define MAXDIGIT 34
void SCI1_printf(char *format,...)
{
	va_list arg_ptr;
	char buf[MAXDIGIT];
	unsigned char flag=0;  /*%d:bit2 l:bit1 %:bit0 */
	unsigned char digit=0; /* 桁数 */
	unsigned char minus=0;
	char fill,format1;
	unsigned char radix; /*N進基数*/
	char sign;
	char *ptr; /*出力文字ポインタ*/
	unsigned char cntr; /*出力文字数カウンタ*/
	unsigned char shift; /*16進シフト 0 or 6*/
	unsigned char i;
	unsigned long int value;
	va_start(arg_ptr,format);
	while (*format) {
		format1=*format;
		if (flag==0) {
			if (format1=='%') {
				flag=1;
				digit=0;
				fill=' ';
				minus=0;
				radix=0;
				ptr=&buf[MAXDIGIT-1];
				*ptr--='\0';
				cntr=0;
				shift=0;
				sign='+';
			} else {
				putCharSCI1(format1);
			}
		} else {
			if (format1=='l') {
				flag|=2;
			} else if ('0'<=(format1)&&(format1)<='9') {
				if (digit==0 && format1=='0') {
					fill='0';
				} else {
					digit=digit*10+((format1)-'0');
					if (MAXDIGIT-2<digit) digit=MAXDIGIT-2;
				}
			} else if (format1=='-') {
				minus=1;
			} else if (format1=='d') {
				flag|=4;
				radix=10;
			} else if (format1=='u') {
				radix=10;
			} else if (format1=='x') {
				radix=16;
			} else if (format1=='X') {
				radix=16;shift=16;
			} else if (format1=='o') {
				radix=8;
			} else if (format1=='b') {
				radix=2;
			} else if (format1=='p') {
				radix=16;shift=16;digit=8;fill='0';flag|=2;
			} else if (format1=='c') {
				putCharSCI1((unsigned char)(va_arg(arg_ptr,int)));
				flag=0;
			} else if (format1=='s') {
				if (digit) {
					cntr=0;ptr=va_arg(arg_ptr,char *);
					while (ptr[cntr]) cntr++; /*cntrは文字数*/
					if (!minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
					putStringSCI1(ptr);
					if (minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
				} else {
					putStringSCI1(va_arg(arg_ptr,char *));
				}
				flag=0;
			} else {
				putCharSCI1(format1);
				flag=0;
			}
			if (radix) {
				switch (flag&6) {
				case 0: /* unsig int */
					value=(unsigned int)va_arg(arg_ptr,int);
					break;
				case 2: /* unsig long int */
					value=va_arg(arg_ptr,long int);
					break;
				case 4: /* sig int */
					value=(long int)va_arg(arg_ptr,int);
					if ((long int)value<0) {
						value=-(long int)value;
						sign='-';
					}
					break;
				case 6: /* sig long int */
					value=va_arg(arg_ptr,long int);
					if ((long int)value<0) {
						value=-(long int)value;
						sign='-';
					}
					break;
				default:
					break;
				}
				while (value) {
					*ptr--=hexstring[value%radix+shift];
					cntr++;
					value/=radix;
				}
				if (cntr==0) {
					*ptr--='0';
					cntr++;
				}
				if (fill==' ') {
					if (sign=='-') {
						*ptr--='-';
						cntr++;
					}
					if (!minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
					putStringSCI1(++ptr);
					if (minus) for (i=cntr;i<digit;i++) putCharSCI1(' ');
				} else {
					for (;cntr<digit-1;cntr++) *ptr--='0';
					if (sign!='-'&&cntr<digit) *ptr--='0';
					else if (sign=='-') *ptr--='-';
					putStringSCI1(++ptr);
				}
				flag=0;
			}
		}
		format++;
	}
}

/* ------------------------------------------------- */
/*                 LED INITIALIZATION                */
/* ------------------------------------------------- */
/*LEDのbitすなわちポートEのbit9,bit11（PEのHのbit1,bit3）を出力に設定*/
/*void initLed(void)
{
	PFC.PEIOR.BYTE.H |= 0x0a;
}*/
#define initLed() (PFC.PEIOR.BYTE.H |= 0x0a)

/* ------------------------------------------------- */
/* LET LED ON */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOnLed(short int number)
{	
	static unsigned char mask[]={0x2,0x8};
	PE.DR.BYTE.H |= mask[number];
}

/* ------------------------------------------------- */
/* LET LED OFF */
/* ------------------------------------------------- */
/*numberは0または1*/
void turnOffLed(short int number)
{
	static unsigned char mask[]={0xfd,0xf7};
	PE.DR.BYTE.H &= mask[number];
}

/* ------------------------------------------------- */
/*              PUSH SW INITIALIZATION               */
/* ------------------------------------------------- */
/*PushSWはPEのbit13,15に割り当てられている*/
/*PushSWのポートを入力に設定*/
/*void initPushSW(void)
{
	PFC.PEIOR.BYTE.H &= 0x5f;
}*/
#define initPushSW() (PFC.PEIOR.BYTE.H &= 0x5f)

/* Pushswの状態をそのまま返す */
short int getPushSW(void)
{
	return ((PE.DR.BYTE.H>>5)&0x5);
}

short int checkPushSW(short int number)
/*Pushsw 0,1の状態を調べる　number:0,or 1*/
/*ONなら1、そうでなかったら0を返す*/
{
	short int ret;
	static const unsigned char mask[]={0x20,0x80};
	if (PE.DR.BYTE.H&mask[number&1]) ret=1;
	else ret=0;
	return ret;
}

/* ------------------------------------------------- */
/*              4 BIT SW INITIALIZATION              */
/* ------------------------------------------------- */
/*4BitSWはPBのbit2,3,4,5に割り当てられている*/
/*4bitSWのポートを入力に設定*/
/*void init4BitSW(void)
{
	PFC.PBIOR.BYTE.L &= 0xc3;
}*/
#define init4BitSW() (PFC.PBIOR.BYTE.L &= 0xc3)

/* 4bitswの状態をそのまま返す */
short int get4BitSW(void)
{
	return ((PB.DR.BYTE.L>>2)&0xf);
}

short int check4BitSW(short int number)
/*4bitsw 0,1,2,3の状態を調べる　number:0,1,2,or 4*/
/*ONなら1、そうでなかったら0を返す*/
{
	short int ret;
	static const unsigned char mask[]={4,8,0x10,0x20};
	if (PB.DR.BYTE.L&mask[number&3]) ret=1;
	else ret=0;
	return ret;
}

/* ------------------------------------------------- */
/*         COMPARE MATCH TIMER INITIALIZATION        */
/* ------------------------------------------------- */
/* コンペアマッチタイマによるタイマ割り込みの初期化 */
/* 割り込み間隔は引数peiodで単位はμsecである */
/* 0<period<1170104 なので最長1.170104secまで可能 */
/* チャンネルが２つあるのではchは0,1のどちらかを選ぶ */
/* 割り込みレベルintLebelは1～15にする */
void initCMTInt(unsigned long int period,int ch,int intLebel)
{
	/* φ：28.636MHz */
//	double dblcmcor;
	unsigned long int cmcor;
	unsigned char cks;
	if (period<16000) {
//		dblcmcor=(double)period*(28.636/8.);
		cmcor=period*28636/8000;
		cks=0; /* φ/8 */
	} else if (period<64000) {
//		dblcmcor=(double)period*(28.636/32.);
		cmcor=period*7159/8000;
		cks=1; /* φ/32 */
	} else if (period<256000) {
//		dblcmcor=(double)period*(28.636/128.);
		cmcor=period/4*7159/8000;
		cks=2; /* φ/128 */
	} else {
//		dblcmcor=(double)period*(28.636/512.);
		cmcor=period/16*7159/8000;
		cks=3; /* φ/512 */
	}
	if (ch==0) {
//		CMT0.CMCOR=(unsigned short int)(dblcmcor+0.5);
		CMT.CMSTR.BIT.STR0=0; /* コンペアマッチタイマ0ストップ */
		CMT0.CMCOR=cmcor-1;
		CMT0.CMCSR.BIT.CKS=cks; /* φの設定 */
		CMT0.CMCSR.BIT.CMIE=1; /* 割り込み可設定 */
		INTC.IPRG.BIT._CMT0=intLebel; /* 割り込みコントローラの割り込みレベル */
	} else {
//		CMT1.CMCOR=(unsigned short int)(dblcmcor+0.5);
		CMT.CMSTR.BIT.STR1=0; /* コンペアマッチタイマ1ストップ*/
		CMT1.CMCOR=cmcor-1;
		CMT1.CMCSR.BIT.CKS=cks; /* φの設定 */
		CMT1.CMCSR.BIT.CMIE=1; /* 割り込み可設定 */
		INTC.IPRG.BIT._CMT1=intLebel; /* 割り込みコントローラの割り込みレベル */
	}
}

#define startCMT0()      (CMT.CMSTR.BIT.STR0=1) /* コンペアマッチタイマ0スタート */
#define stopCMT0()       (CMT.CMSTR.BIT.STR0=0) /* コンペアマッチタイマ0ストップ */
#define clearCMFlag0()  (CMT0.CMCSR.BIT.CMF=0) /* コンペアマッチフラッグ0クリア */
#define startCMT1()      (CMT.CMSTR.BIT.STR1=1) /* コンペアマッチタイマ1スタート */
#define stopCMT1()       (CMT.CMSTR.BIT.STR1=0) /* コンペアマッチタイマ1ストップ*/
#define clearCMFlag1()  (CMT1.CMCSR.BIT.CMF=0) /* コンペアマッチフラッグ1クリア */
