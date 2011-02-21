/**
 * @file   Macros.h
 * @brief  STF全体で使用する簡単なマクロ関数を記述する．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef Macros_h
#define Macros_h


// コピーコンストラクタと=演算子関数を無効にするマクロ
// これはクラスの private: 宣言の中で使うべきだ。
// from: google C++ coding styles
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#define DISALLOW_COPY_AND_ASSIGN_1(TypeName,T1) \
  TypeName(const TypeName<T1>&);                \
  void operator=(const TypeName<T1>&)

#define DISALLOW_COPY_AND_ASSIGN_2(TypeName,T1,T2) \
  TypeName(const TypeName<T1,T2>&);                \
  void operator=(const TypeName<T1,T2>&)

#define DISALLOW_COPY_AND_ASSIGN_3(TypeName,T1,T2,T3) \
  TypeName(const TypeName<T1,T2,T3>&);                \
  void operator=(const TypeName<T1,T2,T3>&)

#define DISALLOW_COPY_AND_ASSIGN_4(TypeName,T1,T2,T3,T4) \
  TypeName(const TypeName<T1,T2,T3,T4>&);                \
  void operator=(const TypeName<T1,T2,T3,T4>&)


#endif // Macros_h