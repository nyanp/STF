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


namespace stf {

//! T->Uへの変換可能性をコンパイル時に検出するType Manipulator．
template<class T, class U>
class Conversion
{
	typedef char Small;
	class Big{ char dummy[2]; };
	static Small Test(U);
	static Big Test(...);
	static T MakeT();
public:
	enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
};

template<int> struct CompileTimeError;
template<> struct CompileTimeError<true> {};

}//end of namespace stf

//! コンパイル時表明を行うマクロ．
/*
	LokiのSTATIC_CHECKは関数スコープでしか使えないが，
	こちらはクラススコープでも使える．テンプレートクラスのConcept宣言などに．
*/
#define STF_STATIC_ASSERT(expr,msg) \
    CompileTimeError<((expr) != 0)> ERROR_##msg

//! 型の継承関係をコンパイル時に強制させるStatic Assert.
/*
	derivedの型はbaseと一致するか，baseから派生した型でなければならない．
*/
#define MUST_BE_DERIVED_FROM(derived, base) \
	STF_STATIC_ASSERT((Conversion<derived,base>::exists != 0),IS_NOT_CONVARIANT)


#endif // Macros_h