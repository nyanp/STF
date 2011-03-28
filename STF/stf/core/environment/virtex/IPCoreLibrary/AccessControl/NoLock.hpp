/*!
  \file   NoLock.hpp
  \author TAKISAWA Jun'ichi
  \date   Sun Apr 11 21:54:10 2010
  
  \brief  ダミーリソース管理クラス
  
  AccessControlクラスによるリソース管理を実装したクラスで
  リソース管理を行わない場合にテンプレート引数として指定する。

  リソース確保関数lock()とリソース解放関数unlock()はともに処理
  のない関数であり最終的にはコンパイラの最適化で除去されることを
  期待している。

  参考書籍: 組み込み現場の「C++」プログラミング, 技術評論社, p.144
*/
#ifndef NOLOCK_HPP_
#define NOLOCK_HPP_

namespace nj
{
  namespace lib
  {
    class NoLock
    {
    public:
      //! 擬似リソース確保関数
      inline static void lock(){}
      //! 擬似リソース解放関数
      inline static void unlock(){}
    };
  }
}

#endif /*NOLOCK_HPP_*/
