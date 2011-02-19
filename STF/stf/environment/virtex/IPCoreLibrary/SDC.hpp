/**
 * @file   SDC.hpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/*!
  	\file   SDC.hpp
  	\author IDOBATA Hiroaki
  	\date   Sun July 11 00:59:?? 2010
  
  	\brief  SDcard IPCore ドライバ
  	
  	
  	XILINX社から提供されるSPI通信IPCoreにCRC計算の機能を付け加えた自作コアを
  	Microblazeから操作する際に必要となるプログラムをまとめる。

 	 このドライバではSPIでの通信方式として全二重(Full Duplex)と半二重(Half Duplex)
  	を選択可能である。全二重とはMaster側のデータの送信と同時にSlave側からデータが
  	Master側へ送信される通信モードであり、半二重とはMaster側がデータを送信する際には
  	Slave側は意味のあるデータを送信せず、Master側からのデータ送信後、Master側が
  	クロックを送信するのに合わせてSlave側がデータを送信してくるモードである。
  	このモード指定はこのクラスのコンストラクタで行う。
  	
  	MUTEX等を用いた排他制御に対応するためテンプレートクラスとして実装している。
*/
#ifndef SDC_HPP_
#define SDC_HPP_

#include "./AccessControl/AccessControl.hpp"
#include "SPIParams.hpp"

#include <cstdio> //EOF

namespace nj
{
namespace lib
{

template<typename AC>
class SDC
{
public:		
	//! コンストラクタ
    /*! 
     * 	SPI IP Coreを指定したモードで初期化する。
		\param base_addr IP Core base address
		\param mode SPIの動作モード(MASTER or SLAVE)
		\param d_mode SPIのデータ転送モード(FULL DUPLEX or HALF DUPLEX)
		\param polar SPIのクロック極性(IDLE HIGH or IDLE LOW)
		\param phase SPIのクロック位相(PHASE FIRST or PHASE SECOND)
		\param order SPIのビットオーダー(MSB First or LSB First)
    */
    SDC(unsigned int base_addr,
		SPIParams::OPERATION_MODE mode, SPIParams::DUPLEX_MODE d_mode,
		SPIParams::MANUAL_SLAVE_SELECT_ASSERTION mssa, SPIParams::CLOCK_POLARITY polar,
		SPIParams::CLOCK_PHASE phase, SPIParams::TRANSMISSION_ORDER order,
		SPIParams::LOOPBACK_MODE loopback);
      
    //! デストラクタ
    /*!
		SPI IP Coreを無効化して終了する。
    */
    ~SDC();
      
    //! 1Byte送信メソッド
    /*!
      	引数として指定されたデータを送信する。
      	返り値は正常に送信が行えた場合には送信したデータである。
       	送信バッファが満杯でさらにデータを追加できなかった場合にはエラーとなりEOFが返る。
	
		\return 正常送信が行えた場合送信したデータ。エラーの場合EOF
    */
    int putchar(int c);
      
    void puts(const unsigned char s[], const unsigned int len);
    //! 1Byte受信メソッド
    /*! 
		1Byteのデータを受信する。
		返り値は受信データがある場合には受信したデータ、
		受信バッファが空であり、受信データが無い場合にはEOFを返す。
				  
		\return 受信データ。エラーの場合はEOF。
    */
    int getchar();

	unsigned char* gets(unsigned char s[], const unsigned int len);
                
    void select_slave(unsigned int id)
    {
     	SPISSR_ = ~(1<<id);
    }
      
    void release_slave()
    {
      	SPISSR_ = 0xffffffff;
    }
      
    //! Mode-Faultが検知された場合真を返す。このメソッドを呼び出すことで、エラーはクリアされる。
    bool is_mode_fault_error()
    {
      	return SPISR_ & SPISR_MODF_ ? true : false;
    }
      
    //! Tx FIFOが満杯の場合trueを返す。
    bool is_tx_fifo_full()
    {
      	return SPISR_ & SPISR_Tx_FULL_ ? true : false;
    }
      
    //! Tx FIFOが空の場合trueを返す。
    bool is_tx_fifo_empty()
    {
      	return SPISR_ & SPISR_Tx_EMPTY_ ? true : false;
    }
      
    //! Rx FIFOが満杯の場合trueを返す。
    bool is_rx_fifo_full()
    {
      	return SPISR_ & SPISR_Rx_FULL_ ? true : false;
    }
      
    //! Rx FIFOが空の場合trueを返す。
    bool is_rx_fifo_empty()
    {
      	return SPISR_ & SPISR_Rx_EMPTY_ ? true : false;
    }

    //! SPIコアのソフトウェアリセットを行うメソッド
    void reset()
    {
     	SRR_ = SRR_VALUE_;
    }

    //! Tx FIFOのリセットを行う。
    void reset_tx_fifo()
    {
      	SPICR_ |= SPICR_Tx_FIFO_RESET_;
    }
      
    //! Rx FIFOのリセットを行う。
    void reset_rx_fifo()
    {
      	SPICR_ |= SPICR_Rx_FIFO_RESET_;
    }
    
    //! CRC7を計算する
    unsigned char calc_crc7(unsigned char *data, unsigned int len)
    {
    	for(unsigned int i = 0; i < len; i++){
			CRCIR_ = CRC7_DATA_VALID_ | data[i];
			CRCIR_ = data[i];
    	}
		CRCIR_ = CRC7_READ_;
		CRCIR_ = 0x00000000;
		return CRCOR_ & 0x7f;
	}
    //! CRC16を計算する
    unsigned short calc_crc16(unsigned char *data, unsigned int len)
    {	
    	unsigned int data_mask;
    	for(unsigned int i = 0; i < len; i++){
    		data_mask = data[i] << 16;
			CRCIR_ = CRC16_DATA_VALID_ | data_mask;
			CRCIR_ = data_mask;
    	}
		CRCIR_ = CRC16_READ_;
		CRCIR_ = 0x00000000;
		return (CRCOR_ >> 8) & 0xffff;
	}
    
    //! 
      
private:      
    //! Software Reset Register
    /*!
		書き込みのみ可能なレジスタ。
		このレジスタに0x0000000aを書き込むことでSPIコアのソフトウェアリセットを行うことができる。
		これ以外の値を書き込んだ場合の動作は未定義であり、行ってはならない。
		このレジスタを読み出した場合の値は不定である。
    */
    volatile unsigned int &SRR_;

    //! SPI Control Register
    /*! 
		SPIの動作設定を行う読み書き可能レジスタ。レジスタの内容は仕様書参照。
    */
    volatile unsigned int &SPICR_;

    //! SPI Status Register
    /*! 
		読み出しのみ可能なレジスタであり、SPIコアのステータスを保持している。
		このレジスタへの書き込みを行っても変化は生じない。
		レジスタの内容については仕様書参照。
    */
    volatile unsigned int &SPISR_;

    //! SPI Data Transmit Register 
    /*! 
		書き込みのみ可能なレジスタであり、SPIでの送信データを書き込む。
		SPIがMasterモードならSPEビットが1であればデータがシフトレジスタへ移動される。
		また、Slaveモードの場合、SPISELがアクティブであればデータの移動が行われる。
							
		既にシフトレジスタにデータが存在する場合には、SPIDTRのデータはシフトレジスタ
		が空になった時点でロードされ連続送信される。
					
		SPIDTRにデータが存在する時点でさらに書き込みを行うと情報は上書きされる。
							
		送信用FIFOが設定されている場合にはこのレジスタへの書き込みはこのFIFOへの書き込みとなる。
    */
    volatile unsigned int &SPIDTR_;

    //! SPI Data Receive Register
    /*! 
		読み出しのみ可能なレジスタであり、受信したデータが格納される。
		double buffered registerである(受信用FIFOが存在する場合もある)。
		このレジスタには受信が完了する度に受信データが書き込まれ、もし読み出しが
		行われずバッファがfullになった場合にはover-run errorとなる。
				
		このレジスタが空の状態で読み出しを行うとエラーとなる。また書き込みを行った
		場合の挙動は定義されない。
    */
    volatile unsigned int &SPIDRR_;

    //! SPI Slave Select Register
    /*! 
		読み書き可能なレジスタであり、Slaveの選択を行う。
		このレジスタで0となっているビットに対応するSlaveとの通信が行われる。
    */
    volatile unsigned int &SPISSR_;

    //! SPI Transmit FIFO Occupancy Register
    /*! 
		読み出しのみ可能なレジスタであり、送信FIFOの保持しているデータ数-1を表示する。
		ハードウェアのコンフィギュレーション次第では存在しない場合もある。
						
		このレジスタへの書き込みや、FIFOが空の場合の読み出しは無視される。
		FIFOが空であるかの唯一の判定法はSPISRのTx_Empty bitを確認することである。
    */
    volatile unsigned int &SPITFOR_;

    //! SPI Receive FIFO Occupancy Register 
    /*! 
		読み出しのみ可能なレジスタであり、受信FIFOの保持しているデータ数-1を表示する。
		ハードウェアのコンフィギュレーション次第では存在しない場合もある。
						
		このレジスタへの書き込みや、FIFOが空の場合の読み出しは無視される。
		FIFOが空であるかの唯一の判定法はSPISRのRx_Empty bitを確認することである。
    */
    volatile unsigned int &SPIRFOR_;

    //! Device Global Interrupt Enable Register
    /*! 
		読み書き可能なレジスタであり、SPIコアが割り込み信号を生成するかを決定する。
		GIE(Global Interrupt Enable)ビットに1を書き込むと割り込みが有効となる。
    */
    volatile unsigned int &DGIER_;

    //! IP Interrupt Status Register
    /*! 
		割り込み要因を表示するレジスタ。詳細は仕様書参照。
    */
    volatile unsigned int &IPISR_;

    //! IP Interrupt Enable Register 
    /*! 
		割り込みの有効/無効を設定するレジスタ。詳細は仕様書参照。
    */
    volatile unsigned int &IPIER_;
      
	//! CRC Input Register
    /*! 
		CRCを計算するためのデータ入力用レジスタ。
    */
    volatile unsigned int &CRCIR_;

    //! CRC Output Register 
    /*! 
		計算されたCRCを出力するレジスタ。
    */
    volatile unsigned int &CRCOR_;
    
    //! Base Addressからのレジスタオフセット
    static const unsigned int SRR_OFFSET_ = 0x00000040;
    static const unsigned int CRCIR_OFFSET_ = 0x00000050;
    static const unsigned int CRCOR_OFFSET_ = 0x00000054;
    static const unsigned int SPICR_OFFSET_ = 0x00000060;
    static const unsigned int SPISR_OFFSET_ = 0x00000064;
    static const unsigned int SPIDTR_OFFSET_ = 0x00000068;
    static const unsigned int SPIDRR_OFFSET_ = 0x0000006C;
    static const unsigned int SPISSR_OFFSET_ = 0x00000070;
    static const unsigned int SPITFOR_OFFSET_ = 0x00000074;
    static const unsigned int SPIRFOR_OFFSET_ = 0x00000078;
    static const unsigned int DGIER_OFFSET_ = 0x0000001C;
    static const unsigned int IPISR_OFFSET_ = 0x00000020;
    static const unsigned int IPIER_OFFSET_ = 0x00000028;
    //! SPI Control Register用ビットマスク
    static const unsigned int SPICR_LOOP_ = 0x00000001;
    static const unsigned int SPICR_SPE_ = 0x00000002;
    static const unsigned int SPICR_MASTER_ = 0x00000004;
    static const unsigned int SPICR_CPOL_ =0x00000008;
    static const unsigned int SPICR_CPHA_ = 0x00000010;
    static const unsigned int SPICR_Tx_FIFO_RESET_ = 0x00000020;
    static const unsigned int SPICR_Rx_FIFO_RESET_ = 0x00000040;
    static const unsigned int SPICR_MANUAL_SLAVE_SELECT_ASSERTION_ENABLE_ = 0x00000080;
    static const unsigned int SPICR_MASTER_TRANSACTION_INHIBIT_ = 0x00000100;
    static const unsigned int SPICR_LSB_FIRST_ = 0x00000200;
     
    //! SPI Status Register用ビットマスク
    static const unsigned int SPISR_Rx_EMPTY_ = 0x00000001;
    static const unsigned int SPISR_Rx_FULL_ = 0x00000002;
    static const unsigned int SPISR_Tx_EMPTY_ = 0x00000004;
    static const unsigned int SPISR_Tx_FULL_ = 0x00000008;
    static const unsigned int SPISR_MODF_ = 0x00000010;
    
    //! IP Interrupt Status Register用ビットマスク。IPISRとIPIERで共用する。
    static const unsigned int IPIXR_MODF_ = 0x00000001;
    static const unsigned int IPIXR_SLAVE_MODF_ = 0x00000002;
    static const unsigned int IPIXR_DTR_EMPTY_ = 0x00000004;
    static const unsigned int IPIXR_DTR_UNDER_RUN_ = 0x00000008;
    static const unsigned int IPIXR_DRR_FULL_ = 0x00000010;
    static const unsigned int IPIXR_DRR_OVER_RUN_ = 0x00000020;
    static const unsigned int IPIXR_Tx_FIFO_HALF_EMPTY_ = 0x00000040;
    
    //! SPIコアリセット用のSRRレジスタ値
    static const unsigned int SRR_VALUE_ = 0x0000000a;

	//! CRC Register用ビットマスク
	static const unsigned int CRC7_DATA_VALID_  = 0x00000100;
	static const unsigned int CRC7_READ_        = 0x00000200;
	static const unsigned int CRC16_DATA_VALID_ = 0x01000000;
	static const unsigned int CRC16_READ_       = 0x02000000;
        

    //! データ転送モード(全二重/半二重)保持メンバ
    SPIParams::DUPLEX_MODE d_mode_;
	//! 転送したバイト数を数えるカウンタ。 Half duplexでの処理向け。
	unsigned char transmitted_;
	
    //! SPIモジュールを有効化する。
    void enable_spi_()
    {
     	SPICR_ |= SPICR_SPE_;
    }
     
    //! SPIモジュールを無効化する。
    void disable_spi_()
    {
    	SPICR_ &= ~SPICR_SPE_;
    }
      
    //! SPIをMasterモードに設定する。
    void enable_master_mode_()
    {
    	SPICR_ |= SPICR_MASTER_;
    }
      
    //! SPIをSlaveモードに設定する。
    void enable_slave_mode_()
    {
     	SPICR_ &= ~SPICR_MASTER_;
    }
      
    //! Manual Slave Selectを有効化。
    void enable_manual_slave_select_assertion_()
    {
      	SPICR_ |= SPICR_MANUAL_SLAVE_SELECT_ASSERTION_ENABLE_;
    }
      
    //! Manual Slace Selectを無効化。
    void disable_manual_slave_select_assertion_()
    {
     	SPICR_ &= ~SPICR_MANUAL_SLAVE_SELECT_ASSERTION_ENABLE_;
    }

    //! SPIをClock phase firstに設定する。      
    void enable_clock_phase_first_()
    {
     	SPICR_ &= ~SPICR_CPHA_;
    }
      
    //! SPIをClock phase secondに設定する。
    void enable_clock_phase_second_()
    {
     	SPICR_ |= SPICR_CPHA_;
    }
      
    //! SPIをActive Lowモードに設定する。
    void enable_active_low_()
    {
     	SPICR_ |= SPICR_CPOL_;
    }
      
    //! SPIをActive Highモードに設定する。
    void enable_active_high_()
    {
      	SPICR_ &= ~SPICR_CPOL_;
    }

    //! Master Transaction有効化。
    void enable_master_transaction_()
    {
     	SPICR_ &= ~SPICR_MASTER_TRANSACTION_INHIBIT_;
    }
      	
    //! Master Transaction無効化。
    void disable_master_transaction_()
    {
      	SPICR_ |= SPICR_MASTER_TRANSACTION_INHIBIT_;
    }
      
    //! 転送モードをLSB Firstに設定する。
    void enable_lsb_first_()
    {
     	SPICR_ |= SPICR_LSB_FIRST_;
    }
      
    //! 転送モードをMSB Firstに設定する。
    void enable_msb_first_()
    {
     	SPICR_ &= ~SPICR_LSB_FIRST_;
    }
      
    //! Loopbackモードを有効化する。
    void enable_loopback_()
    {
      	SPICR_ |= SPICR_LOOP_;
    } 
      
    //! Loopbackモードを無効化する。
    void disable_loopback_()
    {
      	SPICR_ &= ~SPICR_LOOP_;
    }

};    

template<typename AC>
SDC<AC>::SDC(unsigned int base_addr,
	 		SPIParams::OPERATION_MODE mode, SPIParams::DUPLEX_MODE d_mode,
	 		SPIParams::MANUAL_SLAVE_SELECT_ASSERTION mssa, SPIParams::CLOCK_POLARITY polar,
		 	SPIParams::CLOCK_PHASE phase, SPIParams::TRANSMISSION_ORDER order,
		 	SPIParams::LOOPBACK_MODE loopback)
  :	SRR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SRR_OFFSET_)),
  	SPICR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPICR_OFFSET_)),
    SPISR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPISR_OFFSET_)),
    SPIDTR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPIDTR_OFFSET_)),
    SPIDRR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPIDRR_OFFSET_)),
    SPISSR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPISSR_OFFSET_)),
    SPITFOR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPITFOR_OFFSET_)),
    SPIRFOR_(*reinterpret_cast<volatile unsigned int*>(base_addr+SPIRFOR_OFFSET_)),
    DGIER_(*reinterpret_cast<volatile unsigned int*>(base_addr+DGIER_OFFSET_)),
    IPISR_(*reinterpret_cast<volatile unsigned int*>(base_addr+IPISR_OFFSET_)),
    IPIER_(*reinterpret_cast<volatile unsigned int*>(base_addr+IPIER_OFFSET_)),
   	CRCIR_(*reinterpret_cast<volatile unsigned int*>(base_addr + CRCIR_OFFSET_)),
   	CRCOR_(*reinterpret_cast<volatile unsigned int*>(base_addr + CRCOR_OFFSET_)),
    d_mode_(d_mode), transmitted_(0)
{
	reset();
    switch(mode){
	case SPIParams::MASTER_MODE:
		enable_master_mode_();
		enable_master_transaction_();
		break;
	case SPIParams::SLAVE_MODE:
		enable_slave_mode_();
		break;
    }
		  
    switch(mssa){
	case SPIParams::ENABLE_MSSA:
		enable_manual_slave_select_assertion_();
		break;
	case SPIParams::DISABLE_MSSA:
		disable_manual_slave_select_assertion_();
		break;
    }
		  
    switch(polar){
    case SPIParams::CLK_IDLE_HIGH:
		enable_active_low_();
		break;
    case SPIParams::CLK_IDLE_LOW:
		enable_active_high_();
		break;
    }
			
    switch(phase){
    case SPIParams::CLK_PHASE_FIRST:
		enable_clock_phase_first_();
		break;
    case SPIParams::CLK_PHASE_SECOND:
		enable_clock_phase_second_();
		break;
    }
			
    switch(order){
    case SPIParams::MSB_FIRST:
		enable_msb_first_();
		break;
	case SPIParams::LSB_FIRST:
		enable_lsb_first_();
		break;
    }
		  
    switch(loopback){
   	case SPIParams::ENABLE_LOOPBACK:
		enable_loopback_();
		break;
	case SPIParams::DISABLE_LOOPBACK:
		disable_loopback_();
		break;
    }
		  
    reset_tx_fifo();
    reset_rx_fifo();
    enable_spi_();
}

template<typename AC>
SDC<AC>::~SDC()
{
	disable_spi_();
}

template<typename AC>
int SDC<AC>::putchar(int c)
{
	return is_tx_fifo_full() ? EOF : (SPIDTR_ = c);
}

template<typename AC>
void SDC<AC>::puts(const unsigned char s[], const unsigned int len)
{
	unsigned int tx = len;
	do
	{
		if(!is_tx_fifo_full() && tx){ SPIDTR_ = s[len-tx]; --tx; }
	}while(tx);
}

template<typename AC>
int SDC<AC>::getchar()
{
	while(!is_tx_fifo_empty()); reset_rx_fifo(); //Tx FIFO吐き出し, Rx FIFOクリア 	
  	SPIDTR_ = 0xff; // ダミーデータ送信 MOSIは変化させずCLKを出力する 
  	while(is_rx_fifo_empty()); // データ受信完了待ち
    return SPIDRR_;
}

template<typename AC>
unsigned char* SDC<AC>::gets(unsigned char s[], const unsigned int len)
{
	while(!is_tx_fifo_empty()); reset_rx_fifo(); // Tx FIFO吐き出し, Rx FIFOクリア
	unsigned int tx = len, rx = len;
	do
	{
		if(!is_tx_fifo_full() && tx){ SPIDTR_ = 0xff; --tx; }
		if(!is_rx_fifo_empty() && rx){ s[len-rx]=SPIDRR_; --rx; }
	}while(rx);
	return s;
}
		
}// namespace lib
}// namespace nj

#endif /*SDC_HPP_*/
