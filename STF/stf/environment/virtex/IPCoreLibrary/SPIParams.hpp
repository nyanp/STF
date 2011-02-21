/*!
  \file   SPIParams.hpp
  \author TAKISAWA Jun'ichi
  \date   Sun Apr 11 22:10:39 2010
  
  \brief  SPI用パラメータ管理クラス
  
  SPIオブジェクト生成の際に、初期設定を指定する目的で利用する
  パラメータをまとめたクラス。

  SPIクラスはアクセス制御の関係上テンプレートクラスとして実装されている。
  異なるアクセス制御方式を用いるSPIオブジェクトを生成する場合のプログラム
  サイズ増大を防ぐ目的でSPIの共通パラメータをこのクラスにまとめる。
*/
#ifndef SPIPARAMS_HPP_
#define SPIPARAMS_HPP_

namespace nj
{
  namespace lib
  {

    class SPIParams
    {
    public:
      //! 動作モードを指定する列挙型
      enum OPERATION_MODE
      {
  	MASTER_MODE,
  	SLAVE_MODE
      };

      //! データ通信モードを指定する列挙型
      enum DUPLEX_MODE
      {
  	FULL_DUPLEX,
  	HALF_DUPLEX
      };
  
      //! クロック極性を指定する列挙型
      enum CLOCK_POLARITY
      {
  	CLK_IDLE_HIGH,
  	CLK_IDLE_LOW
      };
        
      //! クロック位相を指定する列挙型
      enum CLOCK_PHASE
      {
  	CLK_PHASE_FIRST,
  	CLK_PHASE_SECOND
      };
  
      //! 転送ビットオーダーを指定する列挙型
      enum TRANSMISSION_ORDER
      {
  	MSB_FIRST,
  	LSB_FIRST
      };
  
      //! ハードウェアループバックの有効/無効を指定する列挙型
      enum LOOPBACK_MODE
      {
  	ENABLE_LOOPBACK,
  	DISABLE_LOOPBACK
      };
  
      //! 手動でのSlave Select制御の有無を指定する列挙型
      enum MANUAL_SLAVE_SELECT_ASSERTION
      {
  	ENABLE_MSSA,
  	DISABLE_MSSA
      };
    };

  } // nj::lib
} // nj

#endif /*SPIPARAMS_HPP_*/
