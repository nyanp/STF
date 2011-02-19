/**
 * @file   AccessControl.hpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
/*!
  \file   AccessControl.hpp
  \author TAKISAWA Jun'ichi
  \date   Sun Apr 11 21:28:01 2010
  
  \brief  リソース管理用テンプレートクラス
  
  IPCoreを取り扱うなどリソース確保が必要な場合に用いる。

  テンプレート引数となるクラスが満たす条件は、そのクラスに
  静的メンバ関数としてリソース確保を行うlock()関数とリソース
  解放を行うunlock()関数が定義されていることである。

  このテンプレートクラスはRAII(Resource Acquision Is Initialization)
  の考えに基づき、コンストラクタでテンプレート引数のlock()メソッドを
  呼び出してリソース確保を行い、デストラクタで、unlock()メソッドを呼
  び出すことで確実なリソース解放を保証する。

  参考書籍: 組み込み現場の「C++」プログラミング, 技術評論社, p.143
*/
#ifndef ACCESSCONTROL_HPP_
#define ACCESSCONTROL_HPP_

namespace nj
{
  namespace lib
  {

    template<typename mechanism>
    class AccessControl
    {
    public:
      //! コンストラクタ
      /*! 
				リソースの確保を行う。
				テンプレート引数で指定されたリソース管理クラスのlock()関数
				を呼び出し、リソースを確保する。
      */
      AccessControl()
      {
	mechanism::lock();
      }
      
      //! デストラクタ
      /*! 
				リソースの解放を行う。
				テンプレート引数で指定されたリソース管理クラスのunlock()関数
				を呼び出し、リソースを開放する。
       */
      ~AccessControl()
      {
	mechanism::unlock();
      }
    };

  }
}

#endif /*ACCESSCONTROL_HPP_*/
