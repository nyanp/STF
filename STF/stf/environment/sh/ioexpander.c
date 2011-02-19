/*****************************/
/* IO Expander制御用コード   */
/* PRISM FM用                */
/* Author:小松満仁           */
/* Last updated: 08/11/22    */
/*****************************/

#include "iodefine.h"
#include "ioexpander.h"
#include "nand.h"
#include "sciutil.h"
#include "flags.h"

#define IOE_SW PA.DR.BIT.B16
#define INPUT 0
#define OUTPUT 1


unsigned char ioe_power_on(void)
{
	IOE_SW = 0;//負論理(Active low)
	NAND_WP = 1;
	IOENAC.P6IOR.BIT.B1 = OUTPUT;//NAND-WP
	NAND_WP = 1;
	return 1;
}

unsigned char ioe_power_off(void)
{
	IOE_SW = 1;//負論理(Active low)
	//この後、各IOEの先頭アドレスへの書き込みサイクルを実行すること。
	//ただし書き込むデータは0x00である必要がある。
	IOENAC.P0DR.BYTE = 0x00;
	IOEWAC.P0DR.BYTE = 0x00;
	
	return 1;
}

unsigned char ioe_power_off_2(void)
{
	IOE_SW = 1;//負論理(Active low)
	//この後、各IOEの先頭アドレスへの書き込みサイクルを実行すること。
	//ただし書き込むデータは0x00である必要がある。
//	IOENAC.P0DR.BYTE = 0x00;
//	IOEWAC.P0DR.BYTE = 0x00;
	
	return 1;
}

unsigned char ioe_nac_init(void)
{
	int i=0;
	
	/// NAC制御用初期化
	IOENAC.P3IOR.BIT.B0 = 1;	// SW-NAC3,		Output
	IOENAC.P3IOR.BIT.B1 = 1;	// @SW05, 		Output
	IOENAC.P3IOR.BIT.B2 = 0;	// N-T-OUT, 	Input
	IOENAC.P3IOR.BIT.B3 = 1;	// N-S-EN,		Output
	IOENAC.P3IOR.BIT.B4 = 1;	// N-X-LOAD,	Output
	IOENAC.P3IOR.BIT.B5 = 0;	// N-LSTLIN,	Input
	IOENAC.P3IOR.BIT.B6 = 1;	// N-Y-CLK,		Output
	IOENAC.P3IOR.BIT.B7 = 1;	// N-X-STRT,	Output	

	IOENAC.P4IOR.BIT.B0 = 1;	// N-SYSRES,	Output
	IOENAC.P4IOR.BIT.B1 = 1;	// N-SSSTOP,	Output
	IOENAC.P4IOR.BIT.B2 = 1;	// N-SSSTRT,	Output
	IOENAC.P4IOR.BIT.B3 = 0;	// N-PXLVLD,	Input
	IOENAC.P4IOR.BIT.B4 = 1;	// N-OE,		Output
	IOENAC.P4IOR.BIT.B5 = 1;	// N-RE,		Output
	IOENAC.P4IOR.BIT.B6 = 1;	// N-WRST,		Output		
	IOENAC.P4IOR.BIT.B7 = 1;	// N-RRST,		Output
	
	IOENAC.P5IOR.BIT.B0 = 1;	// N-WE-OBC,	Output	
	IOENAC.P5IOR.BIT.B1 = 1;	// INA(Motor),	Output
	IOENAC.P5IOR.BIT.B2 = 1;	// INB(Motor),	Output
//	IOENAC.P5IOR.BIT.B3 = 0;	// O-LIMIT,		Input
//	IOENAC.P5IOR.BIT.B4 = 0;	// L-LIMIT,		Input	

	IOENAC.P5IOR.BIT.B3 = 1;	// O-LIMIT,		Output
	IOENAC.P5IOR.BIT.B4 = 1;	// L-LIMIT,		Output
	
	/***/
	IOE_N_S_EN 		= 0;
	IOE_N_X_LOAD	= 0;
	IOE_N_Y_CLK		= 0;
	IOE_N_Y_STRT	= 0;
	
	IOE_N_SYSRES 	= 0;
	IOE_N_SSSTOP 	= 0;	
	IOE_N_SSSTRT	= 0;

	IOE_N_OE	 	= 0;
	IOE_N_RE	 	= 0;
	IOE_N_WRST	 	= 0;
	IOE_N_RRST	 	= 0;

	IOE_N_WE_OBC 	= 0;
	IOE_INA		 	= 0;
	IOE_INB		 	= 0;
	IOE_O_LIMIT	 	= 0;
	IOE_L_LIMIT	 	= 0;
	
	PE.DRL.BIT.B10			=	 0; //2008 11/22 NSDATAの処理
	PE.DRL.BIT.B8			= 	 0; //2008 11/22 N-SCLKの処理
	PA.DR.BIT.B18			=    0; //2008 11/22 N-SRCKの処理
	
	for(i=0;i<10000;i++)
	{
	}
	
	IOE_SW_NAC3  = 1;			// NAC 3.3V Off	Active Low
	IOE_SWO5	 = 0;			// NAC 5V	Off	Active High
	
	return 1;
}

unsigned char ioe_focus_init(void)
{
	IOE_INA	= 0;
	IOE_INB	= 0;
	//入出力の決定
	IOENAC.P5IOR.BIT.B1 = OUTPUT;//INA
	IOENAC.P5IOR.BIT.B2 = OUTPUT;//INB
	IOENAC.P5IOR.BIT.B3 = INPUT; //O-LIMIT
	IOENAC.P5IOR.BIT.B4 = INPUT; //L-LIMIT
	
	return 1;
}


unsigned char ioe_magsensor_init(void)
{
	IOE_STA_MGX = 0;//STA_MG* はデフォルトで0
	IOE_STA_MGY = 0;
	IOE_STA_MGZ = 0;
	
	//入出力の決定
	IOENAC.P0IOR.BIT.B0 = OUTPUT;//STA-MGX
	IOENAC.P0IOR.BIT.B1 = OUTPUT;//STA-MGY
	IOENAC.P0IOR.BIT.B2 = OUTPUT;//STA-MGZ
	
	return 1;
}

unsigned char ioe_mtq_init(void)
{
	unsigned long int i=0;
	
	IOE_MTQX_DA = 0;
	IOE_MTQX_DB = 0;
	IOE_MTQY_DA = 0;
	IOE_MTQY_DB = 0;
	IOE_MTQZ_DA = 0;
	IOE_MTQZ_DB = 0;
	
	for(i=0;i<1000;i++)
	{
		
	}
	
	//入出力を決定
	IOENAC.P1IOR.BIT.B0 = OUTPUT;//MTQX-DA
	IOENAC.P1IOR.BIT.B1 = OUTPUT;//MTQX-DB
	IOENAC.P1IOR.BIT.B2 = OUTPUT;//MTQY-DA
	IOENAC.P1IOR.BIT.B3 = OUTPUT;//MTQY-DB
	IOENAC.P1IOR.BIT.B4 = OUTPUT;//MTQZ-DA
	IOENAC.P1IOR.BIT.B5 = OUTPUT;//MTQZ-DB
	
	
	return 1;
}

unsigned char ioe_sunsensor_init(void)
{
	IOE_SS_MPX0 = 0;// SS_MPX*はデフォルトでゼロ
	IOE_SS_MPX1 = 0;
	IOE_SS_MPX2 = 0;
	IOE_SS_MPX3 = 0;
	IOE_SS_MPX4 = 0;// SS_MPX*はデフォルトでゼロ
	IOE_SS_MPX5 = 0;
	IOE_SS_MPX6 = 0;
	IOE_SS_MPX7 = 0;
	IOE_SW_SUN = 1;//サンセンサ電源はデフォルトでOFF (Active low) → PR1-DRW-E-07001G.xlsの情報に基づく
	
	//入出力を決定
	IOENAC.P0IOR.BIT.B3 = OUTPUT;//SS-MPX0
	IOENAC.P0IOR.BIT.B4 = OUTPUT;//SS-MPX1
	IOENAC.P0IOR.BIT.B5 = OUTPUT;//SS-MPX2
	IOENAC.P0IOR.BIT.B6 = OUTPUT;//SS-MPX3
	IOENAC.P2IOR.BIT.B2 = OUTPUT;//SS-MPX4
	IOENAC.P2IOR.BIT.B6 = OUTPUT;//SS-MPX5
	IOENAC.P5IOR.BIT.B6 = OUTPUT;//SS-MPX6
	IOENAC.P6IOR.BIT.B3 = OUTPUT;//SS-MPX7
	IOENAC.P0IOR.BIT.B7 = OUTPUT;//SW-SUN
	IOENAC.P2IOR.BIT.B2 = OUTPUT;//SS-MPX4
	
	return 1;
}

unsigned char ioe_sw_init(void)
{


	return 1;
}

unsigned char ioe_boom_init(void)
{
	IOE_SW_BM_SH	= 0;//ブーム展開信号はデフォルトでOFF
	IOENAC.P2IOR.BIT.B0 = OUTPUT;
	return 1;
}

unsigned char ioe_nachtr_init(void)
{
	IOE_SW_NHTR		= 0;//NACヒータ用信号はデフォルトでOFF
	//SW関係のピンは全て出力に設定されている
	IOENAC.P2IOR.BIT.B4 = OUTPUT;
	return 1;
}

unsigned char ioe_nand_init(void)
{
	unsigned long i;
	
	IOENAC.ODCTL.BIT.B0	= 0;
	IOENAC.ODCTL.BIT.B6	= 0;

	IOE_NAND_CE = 1;
	IOE_NAND_WP = 1;
	
	for(i=0;i<1000;i++)
	{
		
	}
	
	//debug_puts((unsigned char*)"ioe nand init...");

	//入出力設定
	IOENAC.P6IOR.BIT.B0 = 1;//NAND-CE
	IOENAC.P6IOR.BIT.B1 = 1;//NAND-WP

	IOE_NAND_CE = 1;
	IOE_NAND_WP = 1;
	
	for(i=0;i<1000;i++)
	{
		unsigned long j;
		for(j=0;j<4000;j++)
		{
		}
	}
	
	//debug_puts((unsigned char*)"finished.\r\n");
	
	return 1;
}

unsigned char ioe_wac_init(unsigned char index)
{
	unsigned char flag = 1;
	
	switch(index)
	{
		case 0:
			IOEWAC.P0IOR.BYTE	= 0x00;	// W1_DATA,		Input

			IOEWAC.P3IOR.BIT.B0	= 1;	// W1_RCK,		Output
			IOEWAC.P3IOR.BIT.B1	= 1;	// W1_RSTW,		Output
			IOEWAC.P3IOR.BIT.B2	= 1;	// W1_RE,		Output
			IOEWAC.P3IOR.BIT.B3	= 1;	// W1_WEOBC,	Output
			IOEWAC.P3IOR.BIT.B4	= 1;	// W1_OE,		Output
			IOEWAC.P3IOR.BIT.B5	= 1;	// W1_RSTR,		Output
			IOEWAC.P3IOR.BIT.B6	= 0;	// W1_VSYN,		Input
			IOEWAC.P3IOR.BIT.B7	= 1;	// W1_SDA,		Output
			IOEWAC.P4IOR.BIT.B0	= 1;	// W1_SCL,		Output
			IOEWAC.P4IOR.BIT.B1	= 1;	// W1_PWDN,		Output
			
			IOE_W_1_PWDN	= 1;		

			IOE_W_1_RCK	  	= 0;
			IOE_W_1_RSTW  	= 0;
			IOE_W_1_RE	  	= 0;
			IOE_W_1_WEOBC 	= 0;
			IOE_W_1_OE	  	= 0;
			IOE_W_1_RSTR  	= 0;
			IOE_W_1_SDA	  	= 0;
			IOE_W_1_SCL		= 0;
			
			break;
		case 1:
			IOEWAC.P1IOR.BYTE	= 0x00;	// W2_DATA,		Input

			IOEWAC.P4IOR.BIT.B4	= 1;	// W2_RCK,		Output
			IOEWAC.P4IOR.BIT.B5	= 1;	// W2_RSTW,		Output
			IOEWAC.P4IOR.BIT.B6	= 1;	// W2_RE,		Output
			IOEWAC.P4IOR.BIT.B7	= 1;	// W2_WEOBC,	Output
			IOEWAC.P5IOR.BIT.B0	= 1;	// W2_OE,		Output
			IOEWAC.P5IOR.BIT.B1	= 1;	// W2_RSTR,		Output
			IOEWAC.P5IOR.BIT.B2	= 0;	// W2_VSYN,		Input
			IOEWAC.P5IOR.BIT.B3	= 1;	// W2_SDA,		Output
			IOEWAC.P5IOR.BIT.B4	= 1;	// W2_SCL,		Output
			IOEWAC.P5IOR.BIT.B5	= 1;	// W2_PWDN,		Output
			
			IOE_W_2_PWDN	= 1;		
	
			IOE_W_2_RCK	  	= 0;
			IOE_W_2_RSTW  	= 0;
			IOE_W_2_RE	  	= 0;
			IOE_W_2_WEOBC 	= 0;
			IOE_W_2_OE	  	= 0;
			IOE_W_2_RSTR  	= 0;
			IOE_W_2_SDA	  	= 0;
			IOE_W_2_SCL		= 0;
			
			break;
		case 2:
			IOEWAC.P2IOR.BYTE	= 0x00;	// W3_DATA,		Input

			IOEWAC.P6IOR.BIT.B0	= 1;	// W2_RCK,		Output
			IOEWAC.P6IOR.BIT.B1	= 1;	// W2_RSTW,		Output
			IOEWAC.P6IOR.BIT.B2	= 1;	// W2_RE,		Output
			IOEWAC.P6IOR.BIT.B3	= 1;	// W2_WEOBC,	Output
			IOEWAC.P6IOR.BIT.B4	= 1;	// W2_OE,		Output
			IOEWAC.P6IOR.BIT.B5	= 1;	// W2_RSTR,		Output
			IOEWAC.P6IOR.BIT.B6	= 0;	// W2_VSYN,		Input
			IOEWAC.P6IOR.BIT.B7	= 1;	// W2_SDA,		Output
			IOEWAC.P7DIOR.BIT.B0IO	= 1;	// W2_SCL,		Output
			IOEWAC.P7DIOR.BIT.B1IO	= 1;	// W2_PWDN,		Output
	
			IOEWAC.ODCTL.BIT.B0	= 0;
			IOEWAC.ODCTL.BIT.B6	= 0;
			
			IOE_W_3_PWDN	= 1;		

			IOE_W_3_RCK	  	= 0;
			IOE_W_3_RSTW  	= 0;
			IOE_W_3_RE	  	= 0;
			IOE_W_3_WEOBC 	= 0;
			IOE_W_3_OE	  	= 0;
			IOE_W_3_RSTR  	= 0;
			IOE_W_3_SDA	  	= 0;
			IOE_W_3_SCL		= 0;			
			
			break;
		default:
			flag = 0;
			break;
	}
	
	IOE_W_1_PWDN	= 1;	// Turn off the power
	IOE_W_2_PWDN	= 1;	// Turn off the power
	IOE_W_3_PWDN	= 1;	// Turn off the power
				
	return flag;	
}

//ローカルでのみ使用可能なマクロ
//#define IOEWAC.P3IOR.BIT.B7 W1SDA
//#define IOEWAC.P5IOR.BIT.B3 W2SDA
//#define IOEWAC.P6IOR.BIT.B7 W3SDA

unsigned char ioe_wac_set_sda_io(unsigned char index,unsigned char io)
{
	unsigned char flag = 1;
	
	if(io>1)
	{
		flag = 0;
	}
	else
	{
		switch(index)
		{
			case 0:
				IOEWAC.P3IOR.BIT.B7 = io;
				break;
			case 1:
				IOEWAC.P5IOR.BIT.B3 = io;
				break;
			case 2:
				IOEWAC.P6IOR.BIT.B7 = io;
				break;
			default:
				flag = 0;
				break;
		}
	}
	
	return flag;
}

unsigned char ioe_nac_init2(void)
{
	int i=0;
	
	/// NAC制御用初期化
	IOENAC.P3IOR.BIT.B0 = 1;	// SW-NAC3,		Output
	IOENAC.P3IOR.BIT.B1 = 1;	// @SW05, 		Output
	IOENAC.P3IOR.BIT.B2 = 0;	// N-T-OUT, 	Input
	IOENAC.P3IOR.BIT.B3 = 1;	// N-S-EN,		Output
	IOENAC.P3IOR.BIT.B4 = 1;	// N-X-LOAD,	Output
	IOENAC.P3IOR.BIT.B5 = 0;	// N-LSTLIN,	Input
	IOENAC.P3IOR.BIT.B6 = 1;	// N-Y-CLK,		Output
	IOENAC.P3IOR.BIT.B7 = 1;	// N-X-STRT,	Output	

	IOENAC.P4IOR.BIT.B0 = 1;	// N-SYSRES,	Output
	IOENAC.P4IOR.BIT.B1 = 1;	// N-SSSTOP,	Output
	IOENAC.P4IOR.BIT.B2 = 1;	// N-SSSTRT,	Output
	IOENAC.P4IOR.BIT.B3 = 0;	// N-PXLVLD,	Input
	IOENAC.P4IOR.BIT.B4 = 1;	// N-OE,		Output
	IOENAC.P4IOR.BIT.B5 = 1;	// N-RE,		Output
	IOENAC.P4IOR.BIT.B6 = 1;	// N-WRST,		Output		
	IOENAC.P4IOR.BIT.B7 = 1;	// N-RRST,		Output
	
	IOENAC.P5IOR.BIT.B0 = 1;	// N-WE-OBC,	Output	
	IOENAC.P5IOR.BIT.B1 = 1;	// INA(Motor),	Output
	IOENAC.P5IOR.BIT.B2 = 1;	// INB(Motor),	Output
//	IOENAC.P5IOR.BIT.B3 = 0;	// O-LIMIT,		Input
//	IOENAC.P5IOR.BIT.B4 = 0;	// L-LIMIT,		Input	

	IOENAC.P5IOR.BIT.B3 = 1;	// O-LIMIT,		Output
	IOENAC.P5IOR.BIT.B4 = 1;	// L-LIMIT,		Output
	
	for(i=0;i<ioetime_nac*30;i++)
	{
		
	}
	
	/***/
	IOE_N_S_EN 		= 0;
	IOE_N_X_LOAD	= 0;
	IOE_N_Y_CLK		= 0;
	IOE_N_Y_STRT	= 0;
	
	IOE_N_SYSRES 	= 0;
	IOE_N_SSSTOP 	= 0;	
	IOE_N_SSSTRT	= 0;

	IOE_N_OE	 	= 0;
	IOE_N_RE	 	= 0;
	IOE_N_WRST	 	= 0;
	IOE_N_RRST	 	= 0;

	IOE_N_WE_OBC 	= 0;
	IOE_INA		 	= 0;
	IOE_INB		 	= 0;
	IOE_O_LIMIT	 	= 0;
	IOE_L_LIMIT	 	= 0;
	
	for(i=0;i<ioetime_nac*30;i++)
	{
		
	}
	
	PE.DRL.BIT.B10			=	 0; //2008 11/22 NSDATAの処理
	PE.DRL.BIT.B8			= 	 0; //2008 11/22 N-SCLKの処理
	PA.DR.BIT.B18			=    0; //2008 11/22 N-SRCKの処理
	
	for(i=0;i<10000;i++)
	{
	}
	
	IOE_SW_NAC3  = 1;			// NAC 3.3V Off	Active Low
	IOE_SWO5	 = 0;			// NAC 5V	Off	Active High
	
	return 1;
}

unsigned char ioe_focus_init2(void)
{
	int i=0;
	
	IOE_INA	= 0;
	IOE_INB	= 0;
	
	for(i=0;i<ioetime_focus*30;i++)
	{
		
	}
	
	//入出力の決定
	IOENAC.P5IOR.BIT.B1 = OUTPUT;//INA
	IOENAC.P5IOR.BIT.B2 = OUTPUT;//INB
	IOENAC.P5IOR.BIT.B3 = INPUT; //O-LIMIT
	IOENAC.P5IOR.BIT.B4 = INPUT; //L-LIMIT
	
	return 1;
}


unsigned char ioe_magsensor_init2(void)
{
	int i=0;
	
	IOE_STA_MGX = 0;//STA_MG* はデフォルトで0
	IOE_STA_MGY = 0;
	IOE_STA_MGZ = 0;
	
	for(i=0;i<ioetime_ms*30;i++)
	{
		
	}
	
	//入出力の決定
	IOENAC.P0IOR.BIT.B0 = OUTPUT;//STA-MGX
	IOENAC.P0IOR.BIT.B1 = OUTPUT;//STA-MGY
	IOENAC.P0IOR.BIT.B2 = OUTPUT;//STA-MGZ
	
	return 1;
}


unsigned char ioe_mtq_init2(void)
{
	unsigned long int i=0;
	
	IOE_MTQX_DA = 0;
	IOE_MTQX_DB = 0;
	IOE_MTQY_DA = 0;
	IOE_MTQY_DB = 0;
	IOE_MTQZ_DA = 0;
	IOE_MTQZ_DB = 0;
	
	for(i=0;i<ioetime_mtq*30;i++)
	{
		
	}
	
	//入出力を決定
	IOENAC.P1IOR.BIT.B0 = OUTPUT;//MTQX-DA
	IOENAC.P1IOR.BIT.B1 = OUTPUT;//MTQX-DB
	IOENAC.P1IOR.BIT.B2 = OUTPUT;//MTQY-DA
	IOENAC.P1IOR.BIT.B3 = OUTPUT;//MTQY-DB
	IOENAC.P1IOR.BIT.B4 = OUTPUT;//MTQZ-DA
	IOENAC.P1IOR.BIT.B5 = OUTPUT;//MTQZ-DB
	
	
	return 1;
}


unsigned char ioe_sunsensor_init2(void)
{
	int i=0;
	
	IOE_SS_MPX0 = 0;// SS_MPX*はデフォルトでゼロ
	IOE_SS_MPX1 = 0;
	IOE_SS_MPX2 = 0;
	IOE_SS_MPX3 = 0;
	IOE_SS_MPX4 = 0;// SS_MPX*はデフォルトでゼロ
	IOE_SS_MPX5 = 0;
	IOE_SS_MPX6 = 0;
	IOE_SS_MPX7 = 0;
	IOE_SW_SUN = 1;//サンセンサ電源はデフォルトでOFF (Active low) → PR1-DRW-E-07001G.xlsの情報に基づく
	
	for(i=0;i<ioetime_ss*30;i++)
	{
		
	}
	
	//入出力を決定
	IOENAC.P0IOR.BIT.B3 = OUTPUT;//SS-MPX0
	IOENAC.P0IOR.BIT.B4 = OUTPUT;//SS-MPX1
	IOENAC.P0IOR.BIT.B5 = OUTPUT;//SS-MPX2
	IOENAC.P0IOR.BIT.B6 = OUTPUT;//SS-MPX3
	IOENAC.P2IOR.BIT.B2 = OUTPUT;//SS-MPX4
	IOENAC.P2IOR.BIT.B6 = OUTPUT;//SS-MPX5
	IOENAC.P5IOR.BIT.B6 = OUTPUT;//SS-MPX6
	IOENAC.P6IOR.BIT.B3 = OUTPUT;//SS-MPX7
	IOENAC.P0IOR.BIT.B7 = OUTPUT;//SW-SUN
	IOENAC.P2IOR.BIT.B2 = OUTPUT;//SS-MPX4
	
	return 1;
}

unsigned char ioe_boom_init2(void)
{
	int i=0;
	
	IOE_SW_BM_SH	= 0;//ブーム展開信号はデフォルトでOFF
	
	for(i=0;i<ioetime_boom*30;i++)
	{
		
	}
	
	IOENAC.P2IOR.BIT.B0 = OUTPUT;
	return 1;
}

unsigned char ioe_nachtr_init2(void)
{
	int i=0;
	
	IOE_SW_NHTR		= 0;//NACヒータ用信号はデフォルトでOFF
	
	for(i=0;i<ioetime_nhtr*30;i++)
	{
		
	}
	
	//SW関係のピンは全て出力に設定されている
	IOENAC.P2IOR.BIT.B4 = OUTPUT;
	return 1;
}

unsigned char ioe_nand_init2(void)
{
	unsigned long i;
	
	IOENAC.ODCTL.BIT.B0	= 0;
	IOENAC.ODCTL.BIT.B6	= 0;

	IOE_NAND_CE = 1;
	IOE_NAND_WP = 1;
	
	for(i=0;i<ioetime_nand*30;i++)
	{
		
	}
	
	//debug_puts((unsigned char*)"ioe nand init...");

	//入出力設定
	IOENAC.P6IOR.BIT.B0 = 1;//NAND-CE
	IOENAC.P6IOR.BIT.B1 = 1;//NAND-WP

	IOE_NAND_CE = 1;
	IOE_NAND_WP = 1;
	
	for(i=0;i<1000;i++)
	{
		unsigned long j;
		for(j=0;j<4000;j++)
		{
		}
	}
	
	//debug_puts((unsigned char*)"finished.\r\n");
	
	return 1;
}

unsigned char ioe_wac_init2(unsigned char index)
{
	int i=0;
	
	unsigned char flag = 1;
	
	switch(index)
	{
		case 0:
			IOEWAC.P0IOR.BYTE	= 0x00;	// W1_DATA,		Input

			IOEWAC.P3IOR.BIT.B0	= 1;	// W1_RCK,		Output
			IOEWAC.P3IOR.BIT.B1	= 1;	// W1_RSTW,		Output
			IOEWAC.P3IOR.BIT.B2	= 1;	// W1_RE,		Output
			IOEWAC.P3IOR.BIT.B3	= 1;	// W1_WEOBC,	Output
			IOEWAC.P3IOR.BIT.B4	= 1;	// W1_OE,		Output
			IOEWAC.P3IOR.BIT.B5	= 1;	// W1_RSTR,		Output
			IOEWAC.P3IOR.BIT.B6	= 0;	// W1_VSYN,		Input
			IOEWAC.P3IOR.BIT.B7	= 1;	// W1_SDA,		Output
			IOEWAC.P4IOR.BIT.B0	= 1;	// W1_SCL,		Output
			IOEWAC.P4IOR.BIT.B1	= 1;	// W1_PWDN,		Output
			
			for(i=0;i<ioetime_wac*30;i++)
			{
		
			}
	
			IOE_W_1_PWDN	= 1;		

			IOE_W_1_RCK	  	= 0;
			IOE_W_1_RSTW  	= 0;
			IOE_W_1_RE	  	= 0;
			IOE_W_1_WEOBC 	= 0;
			IOE_W_1_OE	  	= 0;
			IOE_W_1_RSTR  	= 0;
			IOE_W_1_SDA	  	= 0;
			IOE_W_1_SCL		= 0;
			
			break;
		case 1:
			IOEWAC.P1IOR.BYTE	= 0x00;	// W2_DATA,		Input

			IOEWAC.P4IOR.BIT.B4	= 1;	// W2_RCK,		Output
			IOEWAC.P4IOR.BIT.B5	= 1;	// W2_RSTW,		Output
			IOEWAC.P4IOR.BIT.B6	= 1;	// W2_RE,		Output
			IOEWAC.P4IOR.BIT.B7	= 1;	// W2_WEOBC,	Output
			IOEWAC.P5IOR.BIT.B0	= 1;	// W2_OE,		Output
			IOEWAC.P5IOR.BIT.B1	= 1;	// W2_RSTR,		Output
			IOEWAC.P5IOR.BIT.B2	= 0;	// W2_VSYN,		Input
			IOEWAC.P5IOR.BIT.B3	= 1;	// W2_SDA,		Output
			IOEWAC.P5IOR.BIT.B4	= 1;	// W2_SCL,		Output
			IOEWAC.P5IOR.BIT.B5	= 1;	// W2_PWDN,		Output
			
			for(i=0;i<ioetime_wac*30;i++)
			{
		
			}
	
			IOE_W_2_PWDN	= 1;		
	
			IOE_W_2_RCK	  	= 0;
			IOE_W_2_RSTW  	= 0;
			IOE_W_2_RE	  	= 0;
			IOE_W_2_WEOBC 	= 0;
			IOE_W_2_OE	  	= 0;
			IOE_W_2_RSTR  	= 0;
			IOE_W_2_SDA	  	= 0;
			IOE_W_2_SCL		= 0;
			
			break;
		case 2:
			IOEWAC.P2IOR.BYTE	= 0x00;	// W3_DATA,		Input

			IOEWAC.P6IOR.BIT.B0	= 1;	// W2_RCK,		Output
			IOEWAC.P6IOR.BIT.B1	= 1;	// W2_RSTW,		Output
			IOEWAC.P6IOR.BIT.B2	= 1;	// W2_RE,		Output
			IOEWAC.P6IOR.BIT.B3	= 1;	// W2_WEOBC,	Output
			IOEWAC.P6IOR.BIT.B4	= 1;	// W2_OE,		Output
			IOEWAC.P6IOR.BIT.B5	= 1;	// W2_RSTR,		Output
			IOEWAC.P6IOR.BIT.B6	= 0;	// W2_VSYN,		Input
			IOEWAC.P6IOR.BIT.B7	= 1;	// W2_SDA,		Output
			IOEWAC.P7DIOR.BIT.B0IO	= 1;	// W2_SCL,		Output
			IOEWAC.P7DIOR.BIT.B1IO	= 1;	// W2_PWDN,		Output
	
			IOEWAC.ODCTL.BIT.B0	= 0;
			IOEWAC.ODCTL.BIT.B6	= 0;
			
			for(i=0;i<ioetime_wac*30;i++)
			{
		
			}
	
			IOE_W_3_PWDN	= 1;		

			IOE_W_3_RCK	  	= 0;
			IOE_W_3_RSTW  	= 0;
			IOE_W_3_RE	  	= 0;
			IOE_W_3_WEOBC 	= 0;
			IOE_W_3_OE	  	= 0;
			IOE_W_3_RSTR  	= 0;
			IOE_W_3_SDA	  	= 0;
			IOE_W_3_SCL		= 0;			
			
			break;
		default:
			flag = 0;
			break;
	}

	for(i=0;i<ioetime_wac*30;i++)
	{

	}
	
	IOE_W_1_PWDN	= 1;	// Turn off the power
	IOE_W_2_PWDN	= 1;	// Turn off the power
	IOE_W_3_PWDN	= 1;	// Turn off the power
				
	return flag;	
}
