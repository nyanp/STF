#ifndef stf_core_devicedriver_IAocsDataInput_h
#define stf_core_devicedriver_IAocsDataInput_h

namespace stf {
namespace core {
namespace devicedriver {

/// 周期的にデータを取得，送信するコンポーネントに対するインターフェース
template<class T>
class IAocsDataInput {
public:
	virtual T getValueInBodyFrame() = 0;
	virtual ~IAocsDataInput() { }
};

template<class T>
class IAocsDataOutput {

};

} /* End of namespace stf::core::component */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_devicedriver_AocsDataInput_h