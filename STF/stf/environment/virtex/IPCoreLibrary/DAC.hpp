/**
 * @file   DAC.hpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/*!
  \file   DAC.hpp
  \author TAKISAWA, Jun'ichi.
  \date   Tue Feb 16 18:21:17 2010
  
  \brief  D/AコンバータIP Coreドライバ
  
  アクセルスペース社が提供するD/AコンバータIP Coreのドライバ。
  アクセルスペース社のD/AコンバータはXILINX社が提供するIP Coreを改修して実装されている。

  提供する機能は各D/Aコンバータチャンネルの有効/無効切り替えと、出力値変更である。

  MUTEX等を用いたアクセス制御を考慮しテンプレートクラスとして実装されている。
*/

#ifndef DAC_HPP_
#define DAC_HPP_

#include "./AccessControl/AccessControl.hpp"

#include <assert.h>
namespace nj
{
  namespace lib
  {
    template<typename AC>
    class DAC
    {
    public:
      //! コンストラクタ
      /*! 
				DAC IP Core の初期化処理を行う。
				引数として、base address、DACチャンネル数、DAC bit数をとる。
				DACチャンネル数とDAC bit数に指定されているデフォルト引数はNano-JASMINEでの値である。
			
				初期化処理ではすべてのDACを無効化し、D/A値を0x00000000に設定する。
			
				\param base_addr DAC IP Core の base address
				\param num_dac IP Core 中のチャンネル数。デフォルト値は4。
				\param dac_bits D/A分解能(bit数)。デフォルト値は12。
      */
      explicit DAC(unsigned int base_addr, 
		   unsigned char num_dac = 4, unsigned char dac_bits = 12);

      //! 全DAC有効化メソッド
      /*!
        DAC IPCore内部の全てのDACを有効化する。
       */
      void enable_all();
      //! 全DACを無効化メソッド
      /*!
        DAC IPCore内部の全てのDACを無効化する。
       */
      void disable_all();

      //! DAC個別有効化メソッド
      /*! 
				引数で指定されたチャンネルのDACを有効化する。
			
				\param num 有効化するDACチャンネル。
      */
      void enable(unsigned char num);
      //! DAC個別無効化メソッド
      /*! 
				引数で指定されたチャンネルのDACを無効化する。
			
				\param num 無効化するDACチャンネル。
      */
      void disable(unsigned char num);
      
      //! DAC出力値指定メソッド
      /*! 
				引数で指定されたチャンネルに出力値を設定する。
			
				\param num 出力を指定するDACチャンネル
				\param value 出力指定値
      */
      void set_value(unsigned char num, unsigned int value);

      //! DAC出力値取得メソッド
      /*! 
				引数で指定されたチャンネルの出力値を取得する。
			
				\param num 取得対象のチャンネル
				\return 指定されたチャンネルの出力値
      */
      unsigned int get_value(unsigned char num) const;
    private:
    	unsigned int base_addr_;
      unsigned char num_dac_;
      unsigned char dac_bits_;
	
      volatile unsigned int &control_reg_;
    };

    template<typename AC>
    DAC<AC>::DAC(unsigned int base_addr,
     unsigned char num_dac, unsigned char dac_bits) :
			base_addr_(base_addr), num_dac_(num_dac), dac_bits_(dac_bits),
			control_reg_(*reinterpret_cast<volatile unsigned int*>(base_addr))
    {
      disable_all();
      for(int i=0; i<num_dac_; ++i)
      {
				set_value(i, 0x00000000);
      }
    }

    template<typename AC>
    void DAC<AC>::enable_all()
    {
      AccessControl<AC> ac_obj;
      control_reg_ = 0xffffffff;
    }

    template<typename AC>
    void DAC<AC>::disable_all()
    {
      AccessControl<AC> ac_obj;
      control_reg_ = 0x00000000;
    }

    template<typename AC>
    void DAC<AC>::enable(unsigned char num)
    {
      assert(num < num_dac_);
	
      unsigned int mask = (0x00000001 << (num_dac_-1-num));

      AccessControl<AC> ac_obj;
      control_reg_ |= mask;
    }

    template<typename AC>
    void DAC<AC>::disable(unsigned char num)
    {
      assert(num < num_dac_);
	
      unsigned int mask = (0x00000001 << (num_dac_-1-num));
	
      AccessControl<AC> ac_obj;
      control_reg_ &= ~mask;
    }

    template<typename AC>
    void DAC<AC>::set_value(unsigned char num, unsigned int value)
    {
      assert(num < num_dac_);
	
      AccessControl<AC> ac_obj;
      *reinterpret_cast<unsigned int*>(base_addr_+4*(num+1)) = value;
    }

    template<typename AC>
    unsigned int DAC<AC>::get_value(unsigned char num) const
    {
      assert(num < num_dac_);
	
      AccessControl<AC> ac_obj;
      return *reinterpret_cast<unsigned int*>(base_addr_+4*(num+1));
    }

  }
}

#endif /*DAC_HPP_*/
