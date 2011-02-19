/**
 * @file   UART.hpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/*!
  \file   UART.hpp
  \author TAKISAWA Jun'ichi.
  \date   Fri Sep 18 18:05:32 2009
  
  \brief  UART IP Core ライブラリ
  
  MicroblazeのUART IP Coreライブラリ。
  UART Coreの各種設定と、状態取得、データ送受の基本機能を提供する。
*/
#ifndef UART_HPP_
#define UART_HPP_

#include "./AccessControl/AccessControl.hpp"

#include <cstdio> //EOF

namespace nj
{
  namespace lib
  {
    template<typename AC>
    class UART
    {
    public:
      //! コンストラクタ
      /*! 
				引数で指定されたBase Addressとクラス内部に保持する
				レジスタオフセット値を用いて、各種レジスタへの参照を初期化する。
				また、送信/受信FIFOのリセット処理を行う。
						
				\param base_addr UART IP CoreのBase Address
      */
      explicit UART(unsigned int base_addr);
	
      //! 1Byte送信メソッド
      /*! 
				UART送信FIFOに送信すべき1Byteを書き込む。
				問題なくFIFOへの書き込みが完了した場合には書き込んだ値を返却し、
				FIFOへの書き込みが不可能であった場合はEOFを返却する。
							
				\param data UART送信データ。
							
				\return 正常終了の場合は送信データ、異常終了の場合はEOF。
      */
      int putchar(int c);

      //! 1Byte受信メソッド
      /*! 
				UART受信FIFOから受信している1Byteを取得する。
				取得すべきデータが存在しない場合にはEOFを返す。
						
				呼び出し側ではデータ受信後に受信エラーが生じていないかのチェックを行う必要がある。
				受信エラーが生じているかどうかはis_receive_error()メンバ関数で判定できる。
				どの受信エラーが発生したかはそれぞれのエラー判定用メンバ関数、
				- is_parity_error()
				- is_frame_error()
				- is_overrun_error()
				を利用して判定できる。
							
				エラー発生後もデータの取得は可能であるが、当然受信エラーによってデータが失われた可能性が残る。
							
				\return UART受信データ。受信データ無しの場合EOF。
      */
      int getchar();
	
      //! 受信異常判定メソッド
      /*! 
				UARTの受信に何らかのエラーが生じているかどうかを判定する。
				より詳しいエラー原因を追求するためには各種エラー判定メソッドを個別に呼び出す必要がある。
							
				\return 受信異常がある場合はture、受信異常が無い場合はfalse。
      */
      bool is_receive_error()
      {
      	return (is_parity_error() | is_frame_error() | is_overrun_error()) ? true : false;
      }
	
      //! パリティエラー判定メソッド
      /*! 
				データ受信でパリティエラーが生じたかどうかを判定する。
				パリティエラーが生じている場合、このメソッドはtrueを返す。
				このエラーフラグは読み出しを行うとクリアされる。
							
				なお、パリティチェック機能が実装されているかどうかはIP Coreのコンフィギュレーションに依存する。
				もし、この機能が実装されていない場合、メソッドは常にfalseを返す。
						
				\return パリティエラーを検出した場合ture、それ以外はfalse。
      */
      bool is_parity_error()
      {
      	return (stat_ & PARITY_ERROR_MASK) ? true : false;
      }

      //! フレームエラー判定メソッド
      /*! 
				UART IP Core は通信のstop bitを検出できない場合をフレーミングエラーとして検出する。
				このメソッドはこのフレームエラーが生じたかどうかを判定する。
				フレームエラーが生じている場合、このメソッドはtrueを返す。
				このエラーフラグは読み出しを行うとクリアされる。
							
				\return フレーミングエラーを検出した場合true、それ以外の場合false。
      */
      bool is_frame_error()
      {
      	return (stat_ & FRAME_ERROR_MASK) ? true : false;
      }

      //! オーバーランエラー判定メソッド
      /*! 
				UART IP Core は受信FIFOがfullの状態でさらにデータを受信した場合をオーバーランエラーとして検出する。
				このメソッドはこのオーバーランエラーが生じたかどうかを判定する。
				オーバーランエラーが生じている場合、このメソッドはtrueを返す。
				このエラーフラグは読み出しを行うとクリアされる。
						
				オーバーランエラーが検出された場合、本来FIFOに書き込まれるべきデータは消失する。
						
				\return オーバーランエラーを検出した場合true、それ以外の場合false。
      */
      bool is_overrun_error()
      {
      	return (stat_ & OVERRUN_ERROR_MASK) ? true : false;
      }

      //! 割り込み有効判定メソッド
      /*! 
				UARTの割り込み機能が有効化されているかどうかを判定するメソッド。
				割り込みが有効化されている場合このメソッドはtrueを返す。
							
				\return 割り込みが有効の場合true、それ以外の場合false。
      */
      bool is_intr_enabled()
      {
      	AccessControl<AC> ac_obj;
      	return (STAT_REG_ & INTR_ENABLED_MASK) ? true : false;
      }
     
      //! 割り込み有効化メソッド
      /*! 
				UARTの割り込み機能を有効化するメソッド。
      */
      void enable_intr()
      {
      	AccessControl<AC> ac_obj;
      	CTRL_REG_ |= ENABLE_INTR_MASK;
      }

      //! 割り込み無効化メソッド
      /*! 
				UARTの割り込みを無効化するメソッド。
      */
      void disable_intr()
      {
      	AccessControl<AC> ac_obj;
      	CTRL_REG_ &= !ENABLE_INTR_MASK;
      }

      //! 送信FIFO full判定メソッド
      /*! 
				送信FIFOがfullかどうかを判定するメソッド。
				送信FIFOがfullの場合このメソッドはtrueを返す。
							
				\return 送信FIFOがfullの場合ture、それ以外の場合false。
      */
      bool is_tx_fifo_full()
      {
      	AccessControl<AC> ac_obj;
      	return (STAT_REG_ & Tx_FIFO_FULL_MASK) ? true : false;
      }

      //! 送信FIFO empty判定メソッド
      /*! 
				送信FIFOが空かどうか判定するメソッド。
				送信FIFOが空の場合このメソッドはtrueを返す。
							
				\return 送信FIFOが空の場合true、それ以外の場合false。
      */
      bool is_tx_fifo_empty()
      {
      	AccessControl<AC> ac_obj;
      	return (STAT_REG_ & Tx_FIFO_EMPTY_MASK) ? true : false;
      }

      //! 受信FIFO full判定メソッド
      /*! 
				受信FIFOがfullかどうか判定するメソッド。
				受信FIFOがfullの場合このメソッドはtrueを返す。
						
				\return 受信FIFOがfullの場合true、それ以外の場合false。
      */
      bool is_rx_fifo_full()
      {
      	AccessControl<AC> ac_obj;
      	return (STAT_REG_ & Rx_FIFO_FULL_MASK) ? true : false;
      }

      //! 受信FIFOデータ判定メソッド
      /*! 
				受信FIFOが有効なデータを保持しているかどうか判定するメソッド。
				受信FIFOが有効なデータを保持している場合、このメソッドはtrueを返す。
							
				\return 受信FIFOが有効なデータを保持している場合true、それ以外はfalse。
      */
      bool is_rx_fifo_valid_data()
      {
      	AccessControl<AC> ac_obj;
      	return (STAT_REG_ & Rx_FIFO_VALID_DATA_MASK) ? true : false;
      }


      //! 受信FIFOリセットメソッド
      /*! 
				受信FIFOのリセットを行う。
				このメソッドを使用すると受信FIFOは全てゼロクリアされる。
      */
      void rst_rx_fifo()
      {
      	AccessControl<AC> ac_obj;
      	CTRL_REG_ |= RST_Rx_FIFO_MASK;
      }

      //! 送信FIFOリセットメソッド
      /*! 
				送信FIFOのリセットを行う。
				このメソッドを使用すると送信FIFOは全てゼロクリアされる。
      */
      void rst_tx_fifo()
      {
      	AccessControl<AC> ac_obj;
      	CTRL_REG_ |= RST_Tx_FIFO_MASK;
      }
      
    private:
      //! UARTの受信FIFOへの参照を保持するメンバ。
      volatile unsigned int &Rx_FIFO_;
      //! UARTの送信FIFOへの参照を保持するメンバ。
      volatile unsigned int &Tx_FIFO_;
      //! UARTの状態レジスタへの参照を保持するメンバ。
      volatile unsigned int &STAT_REG_;
      //! UARTの設定レジスタへの参照を保持するメンバ。
      volatile unsigned int &CTRL_REG_;
	
      //! 各レジスタのBase Addressからのオフセット値を保持する列挙体。
			static const unsigned int Rx_FIFO_OFFSET = 0x00000000;
			static const unsigned int Tx_FIFO_OFFSET = 0x00000004;
			static const unsigned int STAT_REG_OFFSET = 0x00000008;
			static const unsigned int CTRL_REG_OFFSET = 0x0000000c;
	
      //! 状態レジスタの各種ビットマスクを保持する列挙体。
			static const unsigned int PARITY_ERROR_MASK = 0x00000080;
			static const unsigned int FRAME_ERROR_MASK = 0x00000040;
			static const unsigned int OVERRUN_ERROR_MASK = 0x00000020;
			static const unsigned int INTR_ENABLED_MASK = 0x00000010;
			static const unsigned int Tx_FIFO_FULL_MASK = 0x00000008;
			static const unsigned int Tx_FIFO_EMPTY_MASK = 0x00000004;
			static const unsigned int Rx_FIFO_FULL_MASK = 0x00000002;
			static const unsigned int Rx_FIFO_VALID_DATA_MASK = 0x00000001;

      //! 設定レジスタの各種ビットマスクを保持する列挙体。
			static const unsigned int ENABLE_INTR_MASK = 0x00000010;
			static const unsigned int RST_Rx_FIFO_MASK = 0x00000002;
			static const unsigned int RST_Tx_FIFO_MASK = 0x00000001;

      //! STATレジスタのコピーを保持するメンバ
      /*!
				STATレジスタにある受信エラーフラグ類は1度STATレジスタを読み込んでしまうと
				全てクリアされてしまう。このため、各種のエラー判定を行うためには一度STATレジスタの内容を
				別の領域へコピーする必要がある。
      */
      unsigned int stat_;
    };
    
    template<typename AC>
    UART<AC>::UART(unsigned int base_addr) : 
			Rx_FIFO_(*reinterpret_cast<volatile unsigned int*>(base_addr)),
			Tx_FIFO_(*reinterpret_cast<volatile unsigned int*>(base_addr+Tx_FIFO_OFFSET)),
			STAT_REG_(*reinterpret_cast<volatile unsigned int*>(base_addr+STAT_REG_OFFSET)),
			CTRL_REG_(*reinterpret_cast<volatile unsigned int*>(base_addr+CTRL_REG_OFFSET))
    {
      // Tx/Rx FIFO　のリセット
      rst_rx_fifo(); rst_tx_fifo();
    }
		
    template<typename AC>
    int UART<AC>::getchar()
    {
      // IP Core への排他アクセスを取得
      AccessControl<AC> ac_obj;
			
      // 受信エラーに備えフラグコピー
      stat_ = STAT_REG_;
			
      // 受信すべきデータ無し
      if(!is_rx_fifo_valid_data())
      {
				return EOF;
      }
			
      return Rx_FIFO_;
    }

    template<typename AC>
    int UART<AC>::putchar(int c)
    {
      AccessControl<AC> ac_obj;
			
      if(is_tx_fifo_full())
      {
				return EOF;
      } 
      Tx_FIFO_ = static_cast<unsigned int>(0x000000ff & c);
      return c;
    }


  } // namespace nj::lib
} // namespace nj

#endif /*UART_HPP_*/
