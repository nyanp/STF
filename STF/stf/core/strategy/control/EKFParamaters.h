/**
 * @file   EKFParameters.h
 * @brief  ジャイロバイアスEKFの初期値を設定する構造体．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_core_strategy_control_EKFParameters_h
#define aocs_core_strategy_control_EKFParameters_h

#include "../../../datatype/Quaternion.h"
#include "../../../datatype/StaticMatrix.h"
#include "../../../datatype/StaticVector.h"

namespace stf {
namespace core {
namespace strategy {
namespace control {

//! ジャイロバイアスEKFの初期値を設定する構造体．
/*! 
*/
struct EKFParameters {
public:
	EKFParameters(){}
    datatype::Quaternion q0;//! q初期値
    datatype::StaticVector<3> b0;//! b初期値
    datatype::StaticMatrix<6, 6> P0;//! 共分散行列初期値
    double w_q;//! システムノイズ
	double w_b;//! システムノイズ
    double v;//! 観測ノイズベクトル
    double timestep;//! 伝搬時間刻み幅(sec)
    double tau;//! バイアスレートランダムノイズの時定数(non-zero)
	double MinimunGain;//! カルマンゲインKの対角成分に設定される最小値．0の場合は最小値を設定しない通常のKF
	bool calcSensorGap;//! センサ出力遅延の処理
	~EKFParameters(){}
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // aocs_strategy_input_EKFParameters_h
