/**
 * @file   SPI.hpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/*!
  \file   SPI.hpp
  \author TAKISAWA Jun'ichi
  \date   Sun Apr 11 22:03:58 2010
  
  \brief  SPI IPCore ドライバ
  
  XILINX社から提供されるSPI通信IPCoreをMicroblazeから操作する際に必要
  となるプログラムをまとめる。

  このドライバではSPIでの通信方式として全二重(Full Duplex)と半二重(Half Duplex)
  を選択可能である。全二重とはMaster側のデータの送信と同時にSlave側からデータが
  Master側へ送信される通信モードであり、半二重とはMaster側がデータを送信する際には
  Slave側は意味のあるデータを送信せず、Master側からのデータ送信後、Master側が
  クロックを送信するのに合わせてSlave側がデータを送信してくるモードである。
  このモード指定はこのクラスのコンストラクタで行う。

  MUTEX等を用いた排他制御に対応するためテンプレートクラスとして実装している。
*/
#ifndef SPI_HPP_
#define SPI_HPP_

#include "./AccessControl/AccessControl.hpp"
#include "SPIParams.hpp"

#include <cstdio> //EOF

namespace nj
{
  namespace lib
  {
    template<typename AC>
    class SPI
    {
    public:
      //! Slave Select 管理クラス
      class SSKeeper
      {
      public:
      	inline SSKeeper(SPI<AC>& spi, unsigned int id = 0);
      	inline ~SSKeeper();
      private:
      	SPI<AC>& spi_;
      };
      //! コンストラクタ
      /*! 
		SPI IP Coreを指定したモードで初期化する。
				
		\param base_addr IP Core base address
		\param mode SPIの動作モード(MASTER or SLAVE)
		\param d_mode SPIのデータ転送モード(FULL DUPLEX or HALF DUPLEX)
		\param polar SPIのクロック極性(IDLE HIGH or IDLE LOW)
		\param phase SPIのクロック位相(PHASE FIRST or PHASE SECOND)
		\param order SPIのビットオーダー(MSB First or LSB First)
      */
      SPI(unsigned int base_addr,
	  SPIParams::OPERATION_MODE mode, SPIParams::DUPLEX_MODE d_mode,
	  SPIParams::MANUAL_SLAVE_SELECT_ASSERTION mssa, SPIParams::CLOCK_POLARITY polar,
	  SPIParams::CLOCK_PHASE phase, SPIParams::TRANSMISSION_ORDER order,
	  SPIParams::LOOPBACK_MODE loopback);
      
      //! デストラクタ
      /*!
		SPI IP Coreを無効化して終了する。
      */
      ~SPI();
      
      //! 1Byte送信メソッド
      /*!
       	引数として指定されたデータを送信する。
       	返り値は正常に送信が行えた場合には送信したデータである。
       	送信バッファが満杯でさらにデータを追加できなかった場合にはエラーとなりEOFが返る。
	
		\return 正常送信が行えた場合送信したデータ。エラーの場合EOF
      */
      int putchar(int c);
      
      //! 1Byte受信メソッド
      /*! 
		1Byteのデータを受信する。
		返り値は受信データがある場合には受信したデータ、
		受信バッファが空であり、受信データが無い場合にはEOFを返す。
				  
		\return 受信データ。エラーの場合はEOF。
      */
      int getchar();
      
       //! 4Byte送受信メソッド
      /*!
       	引数として指定されたデータを送信する。SLAVEではTxFIFOにデータを書き込むだけである。
       	返り値は正常に送信が行えた場合には、受信(FULL_DUPLEX&Master)/送信(HALF_DUPLEX|Slave)したデータである。
       	送信バッファが満杯でさらにデータを追加できなかった場合にはエラーとなりEOFが返る。
	
		\return 正常送信が行えた場合,受信/送信したデータ。エラーの場合EOF
      */
      unsigned int putint(unsigned int u); 
  
      //! 4Byte受信メソッド
      /*! 
		4Byteのデータを受信する。
		Masterの場合は０ｘｆｆｆｆｆｆｆｆを送信、SlaveはそのままFIFOを読むだけである。
		返り値は受信データがある場合には受信したデータ、
		受信バッファが空であり、受信データが無い場合にはEOFを返す。
  
		\return 受信データ。エラーの場合はEOF。
      */
      unsigned int getint();
      
      //! Mode-Faultが検知された場合真を返す。このメソッドを呼び出すことで、エラーはクリアされる。
      inline bool is_mode_fault_error();
      
      //! Tx FIFOが満杯の場合trueを返す。
      inline bool is_tx_fifo_full();
      
      //! Tx FIFOが空の場合trueを返す。
      inline bool is_tx_fifo_empty();
      
      //! Rx FIFOが満杯の場合trueを返す。
      inline bool is_rx_fifo_full();
      
      //! Rx FIFOが空の場合trueを返す。
      inline bool is_rx_fifo_empty();

      //! SPIコアのソフトウェアリセットを行うメソッド
      inline void reset();

      //! Tx FIFOのリセットを行う。
      inline void reset_tx_fifo();
      
      //! Rx FIFOのリセットを行う。
      void reset_rx_fifo();
      
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

      //! Base Addressからのレジスタオフセット
      static const unsigned int SRR_OFFSET_ = 0x00000040;
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

      //! データ転送モード(全二重/半二重)保持メンバ
      SPIParams::DUPLEX_MODE d_mode_;

      //! SlaveSelect関連処理にアクセスするためのfriend宣言
      friend class SPI<AC>::SSKeeper;
      //! SlaveSelect Lock Counter
      volatile unsigned int ss_locked_;
      //! SS選択
      inline void select_slave_(unsigned int id);      
      //! SS解放
      inline void release_slave_();

      //! SPIモジュールを有効化する。
      inline void enable_spi_();
      
      //! SPIモジュールを無効化する。
      inline void disable_spi_();
      
      //! SPIをMasterモードに設定する。
      inline void enable_master_mode_();
      
      //! SPIをSlaveモードに設定する。
      inline void enable_slave_mode_();
      
      //! Manual Slave Selectを有効化。
      inline void enable_manual_slave_select_assertion_();
      
      //! Manual Slace Selectを無効化。
      inline void disable_manual_slave_select_assertion_();

      //! SPIをClock phase firstに設定する。      
      inline void enable_clock_phase_first_();
      
      //! SPIをClock phase secondに設定する。
      inline void enable_clock_phase_second_();
      
      //! SPIをActive Lowモードに設定する。
      inline void enable_active_low_();
      
      //! SPIをActive Highモードに設定する。
      inline void enable_active_high_();

      //! Master Transaction有効化。
      inline void enable_master_transaction_();
      	
      //! Master Transaction無効化。
      inline void disable_master_transaction_();
      
      //! 転送モードをLSB Firstに設定する。
      inline void enable_lsb_first_();
      
      //! 転送モードをMSB Firstに設定する。
      inline void enable_msb_first_();
      
      //! Loopbackモードを有効化する。
      inline void enable_loopback_();
      
      //! Loopbackモードを無効化する。
      inline void disable_loopback_();      
    };    
#include "SPI_ifs.hpp" // Inline function definisions.
#include "SPI_tfs.hpp" // Template function definisions.
  }
}

#endif /*SPI_HPP_*/
