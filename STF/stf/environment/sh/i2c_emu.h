/**************************************************/
/* IO ExpanderによるI2Cのエミュレーションヘッダ   */
/* PRISM 2ndEM用                                  */
/* Author:田中利樹                                */
/* Last updated: 07/09/11                         */
/**************************************************/
#ifndef __I2C_EMU_H__
#define __I2C_EMU_H__

#include "iodefine.h"
#include "ioexpander.h"

#define SCL_IN IOE_W_1_SCL  		//WAC1_SCL
#define SDA_IN IOE_W_1_SDA  		//WAC_1SDA
#define SCL_REL SCL_IN |= 1;        //SCLをロジックＨに
#define SCL_PUL SCL_IN &= 0;        //SCLをロジックＬに
#define SDA_REL SDA_IN |= 1;        //SDAをロジックＨに
#define SDA_PUL SDA_IN &= 0;        //SDAをロジックＬに

#define W2_SCL_IN 	IOE_W_2_SCL  	//WAC1_SCL
#define W2_SDA_IN 	IOE_W_2_SDA  	//WAC_1SDA
#define W2_SCL_REL 	W2_SCL_IN |= 1; //SCLをロジックＨに
#define W2_SCL_PUL 	W2_SCL_IN &= 0; //SCLをロジックＬに
#define W2_SDA_REL 	W2_SDA_IN |= 1; //SDAをロジックＨに
#define W2_SDA_PUL 	W2_SDA_IN &= 0; //SDAをロジックＬに

#define W3_SCL_IN 	IOE_W_3_SCL  	//WAC1_SCL
#define W3_SDA_IN 	IOE_W_3_SDA  	//WAC_1SDA
#define W3_SCL_REL 	W3_SCL_IN |= 1; //SCLをロジックＨに
#define W3_SCL_PUL 	W3_SCL_IN &= 0; //SCLをロジックＬに
#define W3_SDA_REL 	W3_SDA_IN |= 1; //SDAをロジックＨに
#define W3_SDA_PUL 	W3_SDA_IN &= 0; //SDAをロジックＬに

#define WAIT {volatile int i=30; while(i--);} //i2cCLK調整用
//#define SLAVE_ADDR 0x01;  //WACに依存
//static unsigned char g_i2cbuff = 0x00;

 /* 以下の関数を呼ぶときは割り込みを禁止する */
 
//テスト関数//
void i2c_test(void);
//I2Cをマスタとして初期化//
void i2c_init(void);
//スタートビット発行//
void i2c_startbit(void);
//ストップビット発行//
void i2c_stopbit(void);
//1byte送信//
signed int i2c_send_byte(unsigned char data);
//送信セッション//
unsigned char i2c_write(unsigned char addr, unsigned char data);

//I2Cをマスタとして初期化//
void w2_i2c_init(void);
//スタートビット発行//
void w2_i2c_startbit(void);
//ストップビット発行//
void w2_i2c_stopbit(void);
//1byte送信//
signed int w2_i2c_send_byte(unsigned char data);
//送信セッション//
unsigned char w2_i2c_write(unsigned char addr, unsigned char data);

//I2Cをマスタとして初期化//
void w3_i2c_init(void);
//スタートビット発行//
void w3_i2c_startbit(void);
//ストップビット発行//
void w3_i2c_stopbit(void);
//1byte送信//
signed int w3_i2c_send_byte(unsigned char data);
//送信セッション//
unsigned char w3_i2c_write(unsigned char addr, unsigned char data);

#endif