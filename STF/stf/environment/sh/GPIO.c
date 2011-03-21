/**************************************************/
/* IO ExpanderによるI2Cのエミュレーションコード   */
/* PRISM 2ndEM用                                  */
/* Author:田中利樹                                */
/* Last updated: 07/09/11                         */
/**************************************************/
#include "ioexpander.h"
#include "i2c_emu.h"

#define	FALSE	0
#define TRUE	1

/******************************/
// テスト関数                 //
/******************************/

void i2c_test(void)
{
	/*i2c初期化*/
	i2c_init();

	i2c_write( 0x11, 0x11);//やばい、エラー出る
}

/*******************************/
// I2Cをマスタとして初期化     //
// 小松さんの関数とかぶってる？//
/*******************************/

void i2c_init(void)
{
	 SCL_REL;
	 SDA_REL;
}

void w2_i2c_init(void)
{
	 W2_SCL_REL;
	 W2_SDA_REL;
}

void w3_i2c_init(void)
{
	 W3_SCL_REL;
	 W3_SDA_REL;
}

/***************************************************/
// スタートビット発行関数                          //
// SCLはハイの状態でSDAをローにすることで実現      //
// SDAまたはSCLがすでにローならば他のマスタが使用中//
/***************************************************/

void i2c_startbit(void)
{
	WAIT;
	//SCLかSDAが片方でもローならif文に//
	if(!SCL_IN || !SDA_IN){    
	//以下SCLをローにしてからSDAをハイに//
		if(SCL_IN){
			SCL_PUL;           //ロジックＬに
			WAIT;
		}
		if(!SDA_IN){
			SDA_REL;           //ロジックＨに
			WAIT;
		}
		SCL_REL;               //ロジックＨに
		WAIT;
	}
	//両方ともロジックＨになったら以下の処理//
	SDA_PUL;                   //ロジックＬに
	WAIT;
	SCL_PUL;                   //ロジックＬに
	WAIT;
	/* SCL = SDA = L */
}

void w2_i2c_startbit(void)
{
	WAIT;
	//SCLかSDAが片方でもローならif文に//
	if(!W2_SCL_IN || !W2_SDA_IN){    
	//以下SCLをローにしてからSDAをハイに//
		if(W2_SCL_IN){
			W2_SCL_PUL;           //ロジックＬに
			WAIT;
		}
		if(!W2_SDA_IN){
			W2_SDA_REL;           //ロジックＨに
			WAIT;
		}
		W2_SCL_REL;               //ロジックＨに
		WAIT;
	}
	//両方ともロジックＨになったら以下の処理//
	W2_SDA_PUL;                   //ロジックＬに
	WAIT;
	W2_SCL_PUL;                   //ロジックＬに
	WAIT;
	/* SCL = SDA = L */
}

void w3_i2c_startbit(void)
{
	WAIT;
	//SCLかSDAが片方でもローならif文に//
	if(!W3_SCL_IN || !W3_SDA_IN){    
	//以下SCLをローにしてからSDAをハイに//
		if(W3_SCL_IN){
			W3_SCL_PUL;           //ロジックＬに
			WAIT;
		}
		if(!W3_SDA_IN){
			W3_SDA_REL;           //ロジックＨに
			WAIT;
		}
		W3_SCL_REL;               //ロジックＨに
		WAIT;
	}
	//両方ともロジックＨになったら以下の処理//
	W3_SDA_PUL;                   //ロジックＬに
	WAIT;
	W3_SCL_PUL;                   //ロジックＬに
	WAIT;
	/* SCL = SDA = L */
}

/********************************************************/
// ストップビット発行関数                               //
// マスタはSCLがローの状態でSDAをハイにし、SCLをハイに。//
// その上でSDAをハイにするとストップコンディション達成。//
/********************************************************/

void i2c_stopbit(void)
{
	/* assume SCL = SDA =L*/
	WAIT;
	SCL_REL;
	WAIT;
	SDA_REL;
	WAIT;
	/* SCL = SDA = H */
}

void w2_i2c_stopbit(void)
{
	/* assume SCL = SDA =L*/
	WAIT;
	W2_SCL_REL;
	WAIT;
	W2_SDA_REL;
	WAIT;
	/* SCL = SDA = H */
}

void w3_i2c_stopbit(void)
{
	/* assume SCL = SDA =L*/
	WAIT;
	W3_SCL_REL;
	WAIT;
	W3_SDA_REL;
	WAIT;
	/* SCL = SDA = H */
}

/************************************************************/
// 1byte送信関数                                    　      //
// スレーブはSCLをローに引いてウェイトをかけた状態で、      //
// アドレスの8ビット目で指定された転送方向で通信準備をする。//
// 準備が完了するとSCLをローにひくのをやめる。              //
// これによりSCLはマスタが制御できるようになり、            //
// マスタからのSCLでデータ転送を行えるようになる。          //
// 通信は必ずSCLがローのときにSDAが変化する。               //
// dataを最上位ビットから順にSDAに乗せ、                    //
// SCLの8クロックにより送信。                               //
// 9クロック目でACKビットを取り込む。                       //
// input data                                               //
// output ack                                               //
/************************************************************/

signed int i2c_send_byte(unsigned char data)
{
	/* assume SCL = SDA = L */
	signed int ack;
	volatile int i;
	for(i = 0; i<8; i++){
		if(data & 0x80){  //上位から1bitづつSDAにのせて転送
			SDA_REL;
		}
		else{
			SDA_PUL;
		}
			WAIT;
			WAIT;
			SCL_REL; //SCLがＨの状態でSDAを変更するとstartやstopとなる
			WAIT;
			WAIT;
		if(i != 7){
			data <<= 1;
		}
		SCL_PUL;
	}
	WAIT;
	WAIT;
	SDA_REL;
	SCL_REL;
	WAIT;
	WAIT;
	WAIT;
	/* while(SCL_IN == 0);*/ /* スレーブによるクロックひきのばし */
	ack = SDA_IN;
	WAIT;
	WAIT;
	WAIT;
	WAIT;
	SCL_PUL;
	SDA_PUL;               //ここ同時にやらないとダメかも
	/* SCL = SDA = L */
	return ack;
}

signed int w2_i2c_send_byte(unsigned char data)
{
	/* assume SCL = SDA = L */
	signed int ack;
	volatile int i;
	for(i = 0; i<8; i++){
		if(data & 0x80){  //上位から1bitづつSDAにのせて転送
			W2_SDA_REL;
		}
		else{
			W2_SDA_PUL;
		}
			WAIT;
			WAIT;
			W2_SCL_REL; //SCLがＨの状態でSDAを変更するとstartやstopとなる
			WAIT;
			WAIT;
		if(i != 7){
			data <<= 1;
		}
		W2_SCL_PUL;
	}
	WAIT;
	WAIT;
	W2_SDA_REL;
	W2_SCL_REL;
	WAIT;
	WAIT;
	WAIT;
	/* while(SCL_IN == 0);*/ /* スレーブによるクロックひきのばし */
	ack = W2_SDA_IN;
	WAIT;
	WAIT;
	WAIT;
	WAIT;
	W2_SCL_PUL;
	W2_SDA_PUL;               //ここ同時にやらないとダメかも
	/* SCL = SDA = L */
	return ack;
}

signed int w3_i2c_send_byte(unsigned char data)
{
	/* assume SCL = SDA = L */
	signed int ack;
	volatile int i;
	for(i = 0; i<8; i++){
		if(data & 0x80){  //上位から1bitづつSDAにのせて転送
			W3_SDA_REL;
		}
		else{
			W3_SDA_PUL;
		}
			WAIT;
			WAIT;
			W3_SCL_REL; //SCLがＨの状態でSDAを変更するとstartやstopとなる
			WAIT;
			WAIT;
		if(i != 7){
			data <<= 1;
		}
		W3_SCL_PUL;
	}
	WAIT;
	WAIT;
	W3_SDA_REL;
	W3_SCL_REL;
	WAIT;
	WAIT;
	WAIT;
	/* while(SCL_IN == 0);*/ /* スレーブによるクロックひきのばし */
	ack = W3_SDA_IN;
	WAIT;
	WAIT;
	WAIT;
	WAIT;
	W3_SCL_PUL;
	W3_SDA_PUL;               //ここ同時にやらないとダメかも
	/* SCL = SDA = L */
	return ack;
}

/****************************************************/
// 1byte送信セッション関数                          //
// addrで指定されたスレーブアドレスへ               //
// dataに格納されたデータを送信する。   //
// 途中でNACKが返されると送信が中断されFALSEが帰る。//
// 前後にstartbitとstopbitを配置することに注意。    //
// input addr data                                  //
// output T or F                                    //
/****************************************************/

unsigned char i2c_write(unsigned char addr, unsigned char data){ //元は*dataだった

	i2c_startbit();

	if(i2c_send_byte(0x42) != 0){   //slave address
	//	return FALSE;
	}
	if(i2c_send_byte(addr) != 0){   //nackならfalse
	//	return FALSE;
	}
		if(i2c_send_byte(data) !=0){   //nackならfalse
		//	return FALSE;
		}
	
	i2c_stopbit();	
		
	return TRUE;
}

unsigned char w2_i2c_write(unsigned char addr, unsigned char data){ //元は*dataだった

	w2_i2c_startbit();

	if(w2_i2c_send_byte(0x42) != 0){   //slave address
	//	return FALSE;
	}
	if(w2_i2c_send_byte(addr) != 0){   //nackならfalse
	//	return FALSE;
	}
	if(w2_i2c_send_byte(data) !=0){   //nackならfalse
	//	return FALSE;
	}
	
	w2_i2c_stopbit();	
		
	return TRUE;
}

unsigned char w3_i2c_write(unsigned char addr, unsigned char data){ //元は*dataだった

	w3_i2c_startbit();

	if(w3_i2c_send_byte(0x42) != 0){   //slave address
	//	return FALSE;
	}
	if(w3_i2c_send_byte(addr) != 0){   //nackならfalse
	//	return FALSE;
	}
	if(w3_i2c_send_byte(data) !=0){   //nackならfalse
	//	return FALSE;
	}
	
	w3_i2c_stopbit();	
		
	return TRUE;
}