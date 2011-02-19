/*****************************/
/* IO Expander制御用ヘッダ   */
/* PRISM 2ndEM用             */
/* Author:小松満仁           */
/* Last updated: 07/09/27    */
/*****************************/




#ifndef __IOEXPANDER_H__
#define __IOEXPANDER_H__

//IOExpander用構造体
struct st_ioe
{
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P0DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P0IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P1DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P1IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P2DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P2IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P3DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P3IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P4DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P4IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P5DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P5IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P6DR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P6IOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B3IO:1;
			unsigned char B2IO:1;
			unsigned char B1IO:1;
			unsigned char B0IO:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	P7DIOR;
	union
	{
		unsigned char BYTE;
		struct
		{
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		}	BIT;
	}	ODCTL;
};

/*
 * 注意！！2nd EM用の設定になっています。
 * @see PR1-SPC-E-07002.xls
 */
#define IOEWAC (*(volatile struct st_ioe *)0x00800F40)
#define IOENAC (*(volatile struct st_ioe *)0x00800F80)

/// NAC,ADCS用ピン名称定義
//P0DR
#define IOE_STA_MGX IOENAC.P0DR.BIT.B0
#define IOE_STA_MGY IOENAC.P0DR.BIT.B1
#define IOE_STA_MGZ IOENAC.P0DR.BIT.B2
#define IOE_SS_MPX0 IOENAC.P0DR.BIT.B3
#define IOE_SS_MPX1 IOENAC.P0DR.BIT.B4
#define IOE_SS_MPX2 IOENAC.P0DR.BIT.B5
#define IOE_SS_MPX3 IOENAC.P0DR.BIT.B6
#define IOE_SW_SUN	IOENAC.P0DR.BIT.B7
//P1DR
#define IOE_MTQX_DA IOENAC.P1DR.BIT.B0
#define IOE_MTQX_DB IOENAC.P1DR.BIT.B1
#define IOE_MTQY_DA IOENAC.P1DR.BIT.B2
#define IOE_MTQY_DB IOENAC.P1DR.BIT.B3
#define IOE_MTQZ_DA IOENAC.P1DR.BIT.B4
#define IOE_MTQZ_DB IOENAC.P1DR.BIT.B5
//#define IOE_BLANK	IOENAC.P1DR.BIT.B6
//#define IOE_BLANK	IOENAC.P1DR.BIT.B7
//P2DR
#define IOE_SW_BM_SH IOENAC.P2DR.BIT.B0
//#define IOE_BLANK	 IOENAC.P2DR.BIT.B1
#define IOE_SS_MPX4	 IOENAC.P2DR.BIT.B2
//#define IOE_BLANK	 IOENAC.P2DR.BIT.B3
#define IOE_SW_NHTR	 IOENAC.P2DR.BIT.B4
//#define IOE_BLANK	 IOENAC.P2DR.BIT.B5
#define IOE_SS_MPX5	 IOENAC.P2DR.BIT.B6
//#define IOE_BLANK	 IOENAC.P2DR.BIT.B7
//P3DR
#define IOE_SW_NAC3  IOENAC.P3DR.BIT.B0
#define IOE_SWO5	 IOENAC.P3DR.BIT.B1
#define IOE_N_T_OUT	 IOENAC.P3DR.BIT.B2
#define IOE_N_S_EN	 IOENAC.P3DR.BIT.B3
#define IOE_N_X_LOAD IOENAC.P3DR.BIT.B4
#define IOE_N_LSTLIN IOENAC.P3DR.BIT.B5
#define IOE_N_Y_CLK	 IOENAC.P3DR.BIT.B6
#define IOE_N_Y_STRT IOENAC.P3DR.BIT.B7
//P4DR
#define IOE_N_SYSRES IOENAC.P4DR.BIT.B0
#define IOE_N_SSSTOP IOENAC.P4DR.BIT.B1
#define IOE_N_SSSTRT IOENAC.P4DR.BIT.B2
#define IOE_N_PXLVLD IOENAC.P4DR.BIT.B3
#define IOE_N_OE	 IOENAC.P4DR.BIT.B4
#define IOE_N_RE	 IOENAC.P4DR.BIT.B5
#define IOE_N_WRST	 IOENAC.P4DR.BIT.B6
#define IOE_N_RRST	 IOENAC.P4DR.BIT.B7
//P5DR
#define IOE_N_WE_OBC IOENAC.P5DR.BIT.B0
#define IOE_INA		 IOENAC.P5DR.BIT.B1
#define IOE_INB		 IOENAC.P5DR.BIT.B2
#define IOE_O_LIMIT	 IOENAC.P5DR.BIT.B3
#define IOE_L_LIMIT	 IOENAC.P5DR.BIT.B4
//#define IOE_BLANK	 IOENAC.P5DR.BIT.B5
#define IOE_SS_MPX6	 IOENAC.P5DR.BIT.B6
//#define IOE_BLANK	 IOENAC.P5DR.BIT.B7
//P6DR
#define IOE_NAND_CE IOENAC.P6DR.BIT.B0
#define IOE_NAND_WP	IOENAC.P6DR.BIT.B1
//#define IOE_BLANK	IOENAC.P6DR.BIT.B2
#define IOE_SS_MPX7	IOENAC.P6DR.BIT.B3
//#define IOE_BLANK	IOENAC.P6DR.BIT.B4
//#define IOE_BLANK	IOENAC.P6DR.BIT.B5
//#define IOE_BLANK	IOENAC.P6DR.BIT.B6
//#define IOE_BLANK	IOENAC.P6DR.BIT.B7
//P7は使っていない

///WAC用ピン定義
//P0DR
#define IOE_W_1_DATA IOEWAC.P0DR.BYTE
//P1DR
#define IOE_W_2_DATA IOEWAC.P1DR.BYTE
//P2DR
#define IOE_W_3_DATA IOEWAC.P2DR.BYTE
//P3DR
#define IOE_W_1_RCK	  IOEWAC.P3DR.BIT.B0
#define IOE_W_1_RSTW  IOEWAC.P3DR.BIT.B1
#define IOE_W_1_RE	  IOEWAC.P3DR.BIT.B2
#define IOE_W_1_WEOBC IOEWAC.P3DR.BIT.B3
#define IOE_W_1_OE	  IOEWAC.P3DR.BIT.B4
#define IOE_W_1_RSTR  IOEWAC.P3DR.BIT.B5
#define IOE_W_1_VSYN  IOEWAC.P3DR.BIT.B6
#define IOE_W_1_SDA	  IOEWAC.P3DR.BIT.B7
//P4DR
#define IOE_W_1_SCL	  IOEWAC.P4DR.BIT.B0
#define IOE_W_1_PWDN  IOEWAC.P4DR.BIT.B1
//#define IOE_BLANK	  IOEWAC.P4DR.BIT.B2
//#define IOE_BLANK	  IOEWAC.P4DR.BIT.B3
#define IOE_W_2_RCK	  IOEWAC.P4DR.BIT.B4
#define IOE_W_2_RSTW  IOEWAC.P4DR.BIT.B5
#define IOE_W_2_RE	  IOEWAC.P4DR.BIT.B6
#define IOE_W_2_WEOBC IOEWAC.P4DR.BIT.B7
//P5DR
#define IOE_W_2_OE	  IOEWAC.P5DR.BIT.B0
#define IOE_W_2_RSTR  IOEWAC.P5DR.BIT.B1
#define IOE_W_2_VSYN  IOEWAC.P5DR.BIT.B2
#define IOE_W_2_SDA	  IOEWAC.P5DR.BIT.B3
#define IOE_W_2_SCL	  IOEWAC.P5DR.BIT.B4
#define IOE_W_2_PWDN  IOEWAC.P5DR.BIT.B5
//#define IOE_BLANK	  IOEWAC.P5DR.BIT.B6
//#define IOE_BLANK	  IOEWAC.P5DR.BIT.B7

//P6DR
#define IOE_W_3_RCK	  IOEWAC.P6DR.BIT.B0
#define IOE_W_3_RSTW  IOEWAC.P6DR.BIT.B1
#define IOE_W_3_RE	  IOEWAC.P6DR.BIT.B2
#define IOE_W_3_WEOBC IOEWAC.P6DR.BIT.B3
#define IOE_W_3_OE	  IOEWAC.P6DR.BIT.B4
#define IOE_W_3_RSTR  IOEWAC.P6DR.BIT.B5
#define IOE_W_3_VSYN  IOEWAC.P6DR.BIT.B6
#define IOE_W_3_SDA	  IOEWAC.P6DR.BIT.B7
//P7DR
#define IOE_W_3_SCL	  IOEWAC.P7DIOR.BIT.B0
#define IOE_W_3_PWDN  IOEWAC.P7DIOR.BIT.B1
//#define IOE_BLANK	  IOEWAC.P7DR.BIT.B2
//#define IOE_BLANK	  IOEWAC.P7DR.BIT.B3
//#define IOE_BLANK	  IOEWAC.P7DR.BIT.B4
//#define IOE_BLANK	  IOEWAC.P7DR.BIT.B5
//#define IOE_BLANK	  IOEWAC.P7DR.BIT.B6
//#define IOE_BLANK	  IOEWAC.P7DR.BIT.B7

/// see PR1-FMT-M-07007

unsigned char ioe_power_on(void);
unsigned char ioe_power_off(void);
unsigned char ioe_power_off_2(void);

unsigned char ioe_nac_init(void);
unsigned char ioe_boom_init(void);
unsigned char ioe_nachtr_init(void);
unsigned char ioe_focus_init(void);
unsigned char ioe_magsensor_init(void);
unsigned char ioe_mtq_init(void);
unsigned char ioe_sunsensor_init(void);
unsigned char ioe_nand_init(void);
unsigned char ioe_wac_init(unsigned char index);

unsigned char ioe_nac_init2(void);
unsigned char ioe_boom_init2(void);
unsigned char ioe_nachtr_init2(void);
unsigned char ioe_focus_init2(void);
unsigned char ioe_magsensor_init2(void);
unsigned char ioe_mtq_init2(void);
unsigned char ioe_sunsensor_init2(void);
unsigned char ioe_nand_init2(void);
unsigned char ioe_wac_init2(unsigned char index);

unsigned char ioe_wac_set_sda_io(unsigned char index,unsigned char io);

/// WACの名称の区別の仕方について、キムさん,熱構造系と相談

#define IOE_WAC_A	0
#define IOE_WAC_B	1
#define IOE_WAC_C	2


#endif