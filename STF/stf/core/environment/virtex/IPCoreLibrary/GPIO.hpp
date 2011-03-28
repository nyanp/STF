/*!
  \file   GPIO.hpp
  \author TAKISAWA, Jun'ichi.
  \date   Sun Apr 11 18:03:50 2010
  
  \brief  GPIO IPCore ドライバ
  
  XILINX社から提供されるGPIO IPCoreのドライバプログラム。
  Microblazeを用いてGPIOを操作する場合に必要となるプログラムがまとめられている。
  GPIOはピンのI/Oを規定する"GPIO状態"と実際のピン入出力情報である"GPIOデータ"を管理している。

  参考文書: XILINX DS569 (GPIO IPCore 仕様書)
*/
#ifndef GPIO_HPP_
#define GPIO_HPP_

#include "./AccessControl/AccessControl.hpp"

namespace nj
{
  namespace lib
  {

    template<typename AC>
    class GPIO
    {
    public:
      //! コンストラクタ
      /*! 
				GPIO IPCoreのbase addressを引数にとる。
				引数として渡されたbase addressを利用して、GPIOレジスタの初期設定を行う。
				初期設定では、出力ピンの衝突を防ぐため、すべてのピンを入力ピンとして初期化する。
			
				\param base_addr GPIOコアのbase address
      */
      explicit GPIO(unsigned int base_addr);

      //! GPIO状態一括設定メソッド
      /*! 
				GPIOピンの入出力設定を引数で指定されたものに変更する。
				bitが0の場合は対応するピンが出力に、1の場合は入力に設定される。
			
				\param state GPIOピンの入出力設定
      */
      void set_state(unsigned int state)
      {
				AccessControl<AC> ac_obj;
				GPIO_TRI_ = state;
      }
      
      //! GPIOデータ一括設定メソッド
      /*! 
				GPIOピンの出力を引数で指定されたものに変更する。
				ピンが入力ピンとして設定されている場合、この書き込みは影響を与えない。
			
				\param data GPIOピンへの出力指令
      */
      void set_data(unsigned int data)
      {
				AccessControl<AC> ac_obj;
				GPIO_DATA_ = data;
      }
      
      //! GPIO状態一括取得メソッド
      /*! 
				GPIOの現在のI/O設定を取得する。
				bitが0の場合は対応するピンは出力であり、1の場合は入力である。
			
				\return 現在のI/O設定情報
      */
      unsigned int get_state()
      {
				AccessControl<AC> ac_obj;
				return GPIO_TRI_;
      }

      //! GPIOデータ一括取得メソッド
      /*! 
				GPIOの現在のピン状態を取得する。
				入力に設定されたピンの状態のみが正当であり、設定が出力となっている
				ピンに対応するbitの情報がどうなるかは未定義である。
			  
				\return 現在のピン情報
      */
      unsigned int get_data()
      {
				AccessControl<AC> ac_obj;
				return GPIO_DATA_;
      }
	
      //! GPIO状態ANDメソッド
      /*! 
				GPIOの状態レジスタに引数で指定されたマスクでAND演算を行う。
			
				\param mask ANDマスク
      */
      void state_and(unsigned int mask)
      {
				AccessControl<AC> ac_obj;
				GPIO_TRI_ &= mask;
      }
      
      //! GPIO状態ORメソッド
      /*! 
				GPIOの状態レジスタに引数で指定されたマスクでOR演算を行う。
			
				\param mask ORマスク
      */
      void state_or(unsigned int mask)
      {
				AccessControl<AC> ac_obj;
				GPIO_TRI_ |= mask;
      }
	
      //! GPIO状態XORメソッド
      /*! 
				GPIOの状態レジスタに引数で指定されたマスクでXOR演算を行う。
			
				\param mask XORマスク
      */
      void state_xor(unsigned int mask)
      {
				AccessControl<AC> ac_obj;
				GPIO_TRI_ ^= mask;
      }
	
      //! GPIOデータANDメソッド
      /*! 
				GPIOのデータレジスタに引数で指定されたマスクでAND演算を行う。
			
				\param mask ANDマスク
      */
      void data_and(unsigned int mask)
      {
				AccessControl<AC> ac_obj;
				GPIO_DATA_ &= mask;
      }

      //! GPIOデータORメソッド
      /*! 
				GPIOのデータレジスタに引数で指定されたマスクでOR演算を行う。
			
				\param mask ORマスク
      */
      void data_or(unsigned int mask)
      {
				AccessControl<AC> ac_obj;
				GPIO_DATA_ |= mask;
      }
	

      //! GPIOデータBitAccessメソッド
      /*! 
				GPIOのデータレジスタに引数で指定されたレジスタのみ設定した状態にする
			
				\param status  設定状態　
				\param set 設定レジスタ位置
      */
      void data_bitac(unsigned char status, unsigned char set)
      {
				AccessControl<AC> ac_obj;
				unsigned int trig=0x00000001;

				trig <<= set;
				if(status==1){
					data_or(trig);
				}else{
					data_and(~trig);
				}
      }

      //! GPIOデータXORメソッド
      /*! 
				GPIOのデータレジスタに引数で指定されたマスクでXOR演算を行う。
			
				\param mask XORマスク
      */
      void data_xor(unsigned int mask)
      {
				AccessControl<AC> ac_obj;
				GPIO_DATA_ ^= mask;
      }

    private:
      //! GPIOデータレジスタへの参照
      /*! 
				GPIOが入力に設定された場合、ピンの状態がこのレジスタに格納される。
				GPIOが出力に設定された場合はこのレジスタの状態が実際のピンに出力される。
      */
      volatile unsigned int &GPIO_DATA_;
      //! GPIO設定レジスタへの参照
      /*!
				このレジスタのbitに1を書き込むと、対応するピンは入力ピンとなる。
				逆に、0を書き込めば対応するピンは出力ピンとなる。
      */
      volatile unsigned int &GPIO_TRI_;
      
      //! GPIO_DATA_レジスタとbase addressとのオフセット
      static const unsigned int GPIO_DATA_OFFSET = 0x00000000;
      //! GPIO_TRI_レジスタとbase addressとのオフセット
      static const unsigned int GPIO_TRI_OFFSET = 0x00000004;
    };

    template<typename AC>
    GPIO<AC>::GPIO(unsigned int base_addr) :
      GPIO_DATA_(*reinterpret_cast<volatile unsigned int *>(base_addr)),
      GPIO_TRI_(*reinterpret_cast<volatile unsigned int *>(base_addr + GPIO_TRI_OFFSET))
    {
      AccessControl<AC> ac_obj;
	
      // 初期状態は不用意な事故を避けるため、すべてのGPIOピンを入力とする。
      GPIO_TRI_ = 0xffffffff;
    }


  } // namespace nj::lib
} // namespace nj

#endif /*GPIO_HPP_*/
