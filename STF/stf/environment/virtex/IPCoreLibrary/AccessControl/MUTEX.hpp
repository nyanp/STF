/*!
  \file   MUTEX.hpp
  \author TAKISAWA Jun'ichi
  \date   Sun Apr 11 21:40:30 2010
  
  \brief  MUTEXを用いたリソース管理クラス
  
  複数のMicroblazeから単一のIPCoreにアクセスを行う際に用いられる
  MUTEXによる排他制御を管理するリソース管理クラス。

  AccessControlテンプレートクラスのテンプレート引数として利用する
  ことを想定している。

  一つのMicroblazeが同一MUTEXを複数回確保しようとした場合には、この
  クラス内部で参照カウンタを加算し、MUTEX解放が同一回数行われるまで
  MUTEXを保持する。

  参考書籍: 組み込み現場の「C++」プログラミング, 技術評論社, p.144
  参考文書: XILINX DS631 (MUTEX IPCore 仕様書)
*/
#ifndef MUTEX_HPP_
#define MUTEX_HPP_

//#include <xparameters.h>

namespace nj
{
  namespace lib
  {

    class MUTEX
    {
    public:
      //! MUTEX確保関数
      /*! 
				MUTEXレジスタを操作し、MUTEXの確保を行う。
			
				既にMUTEXが他方のMicroblazeにより確保されている場合には、解放
				されるまで確保を行い続ける。
			
				既にMUTEXを確保した状態でさらにこの関数を呼び出した場合には参
				照カウンタをインクリメントし、回数を記録する。
      */
      inline static void lock()
      {
	//　既にロックされている場合はカウンタを更新するのみ。
	if(lock_counter_++){ return; }
	do
	{
	  MUTEX_ = lock_mask_;
	}while(MUTEX_ != lock_mask_);
      }
      
      //! MUTEX解放関数
      /*! 
				MUTEXレジスタを操作し、MUTEXの解放を行う。
			
				複数回MUTEX確保が行われている場合には参照カウンタをデクリメントし
				確保と同数の解放操作が行われるまでMUTEXを保持し続ける。
       */
      inline static void unlock()
      {
	// 複数回ロックされた場合に最後の開放までロックを維持する。
	if(--lock_counter_){ return; }
	MUTEX_ = unlock_mask_;
      }
    private:
      //! MUTEXレジスタへの参照
      static volatile unsigned int & MUTEX_;
      //! 参照カウンタ
      /*!
				MUTEXの確保回数を記録する。
       */
      static unsigned int lock_counter_;
      //! MUTEXの確保操作に用いるマスク
      static const unsigned int lock_mask_ = (0 << 1) | 0x00000001;
      //! MUTEXの解放操作に用いるマスク
      static const unsigned int unlock_mask_ = (0 << 1);
      
      //! MUTEXの確保操作に用いるマスク
      //static const unsigned int lock_mask_ = (XPAR_CPU_ID << 1) | 0x00000001;
      //! MUTEXの解放操作に用いるマスク
      //static const unsigned int unlock_mask_ = (XPAR_CPU_ID << 1);
    };

  }
}
#endif /*MUTEX_HPP_*/
