/**
 * @file   EKFParamaters.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef aocs_core_strategy_control_EKFParamaters_h
#define aocs_core_strategy_control_EKFParamaters_h

#include "../../../datatype/Quaternion.h"
#include "../../../datatype/Matrix.h"
#include "../../../datatype/Vector.h"


namespace stf {
namespace core {
namespace strategy {
namespace control {

struct EKFParamaters {
public:
    EKFParamaters();
    datatype::Quaternion q0;//q初期値
    datatype::Vector b0;//b初期値
    datatype::Matrix P0;//共分散行列初期値
    double w_q;//システムノイズ
	double w_b;//システムノイズ
    double v;//観測ノイズベクトル
    double timestep;//伝搬時間刻み幅(sec)
    double tau;//バイアスレートランダムノイズの時定数(non-zero)
	double MinimunGain;//カルマンゲインKの対角成分に設定される最小値．0の場合は最小値を設定しない通常のKF
	bool calcSensorGap;//センサ出力遅延の処理
    ~EKFParamaters();
};

} /* End of namespace stf::core::strategy::control */
} /* End of namespace stf::core::strategy */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // aocs_strategy_input_EKFParamaters_h
