/**
 * @file   Macros.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef Macros_h
#define Macros_h

//簡単なマクロ関数を記述する．


// コピーコンストラクタと=演算子関数を無効にするマクロ
// これはクラスの private: 宣言の中で使うべきだ。
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)



#endif // Macros_h