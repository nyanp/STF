/**
 * @file   TypeList.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_util_Typelist_h
#define stf_util_Typelist_h

#include "../datatype/List.h"
#include "../datatype/Quaternion.h"
namespace stf {
namespace util {

/*
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1,T2) Typelist<T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1,T2,T3) Typelist<T1, TYPELIST_2(T2,T3) >
#define TYPELIST_4(T1, T2, T3, T4) \
    Typelist<T1, TYPELIST_3(T2, T3, T4) >
#define TYPELIST_5(T1, T2, T3, T4, T5) \
    Typelist<T1, TYPELIST_4(T2, T3, T4, T5) >
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) \
    Typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6) >
#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
    Typelist<T1, TYPELIST_6(T2, T3, T4, T5, T6, T7) >
#define TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
    Typelist<T1, TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >
#define TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    Typelist<T1, TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >*/



template<class T> struct Holder {
	//datatype::List< T* > value_;
	T value_;
};

class NullType {};
	
template<typename T>
struct Type2Type{
	typedef T OriginalType;
};

template<class T, class U>
struct Typelist
{
	typedef T Head;
	typedef U Tail;
};

template <class TList, template <class,class> class Unit, class Mode>
class GenScatterHierarchy;
     
template <class T1, class T2, template <class,class> class Unit, class Mode>
class GenScatterHierarchy<Typelist<T1, T2>, Unit, Mode>
    : public GenScatterHierarchy<T1, Unit, Mode>
    , public GenScatterHierarchy<T2, Unit, Mode>
{
public:
    typedef Typelist<T1, T2> TList;
    typedef GenScatterHierarchy<T1, Unit, Mode> LeftBase;
    typedef GenScatterHierarchy<T2, Unit, Mode> RightBase;
    template <typename T> struct Rebind
    {
        typedef Unit<T,Mode> Result;
    };
};
     
template <class AtomicType, template <class,class> class Unit, class Mode>
class GenScatterHierarchy : public Unit<AtomicType,Mode>
{
    typedef Unit<AtomicType,Mode> LeftBase;
    template <typename T> struct Rebind
    {
        typedef Unit<T,Mode> Result;
    };
};
    
template <template <class,class> class Unit, class Mode>
class GenScatterHierarchy<NullType, Unit, Mode>
{
    template <typename T> struct Rebind
    {
        typedef Unit<T,Mode> Result;
    };
};

template <class T, class H>
typename H::Rebind<T>::Result& Field(H& obj)
{
    return obj;
}

/*
template <class TList, template <class,class> class Unit>
class GenScatterHierarchy;
     
template <class T1, class T2, template <class,class> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
public:
    typedef Typelist<T1, T2> TList;
    typedef GenScatterHierarchy<T1, Unit> LeftBase;
    typedef GenScatterHierarchy<T2, Unit> RightBase;
    template <typename T,typename U> struct Rebind
    {
        typedef Unit<T,U> Result;
    };
};
     
template <class AtomicType, class Mode, template <class,class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType,Mode>
{
    typedef Unit<AtomicType,Mode> LeftBase;
    template <typename T,typename U> struct Rebind
    {
        typedef Unit<T,U> Result;
    };
};
    
template <template <class,class> class Unit>
class GenScatterHierarchy<NullType, Unit>
{
    template <typename T,typename U> struct Rebind
    {
        typedef Unit<T,U> Result;
    };
};*/

} /* End of namespace stf::util*/
} /* End of namespace stf */

#endif // stf_util_Typelist_h
