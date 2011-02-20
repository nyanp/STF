/**
 * @file   IDataUpdatable.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_devicedriver_IDataUpdatable_h
#define stf_core_devicedriver_IDataUpdatable_h


namespace stf {
namespace core {
namespace devicedriver {

/// 周期的にデータを取得，送信するコンポーネントに対するインターフェース
class IDataUpdatable {
public:
	virtual void do_update()  = 0;
	virtual ~IDataUpdatable() { }
};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_IDataUpdatable_h
