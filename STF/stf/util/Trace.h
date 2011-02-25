/**
 * @file   Trace.h
 * @brief  STFの内部状態を外部ファイルに書き出すためのトレースオブジェクト．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_util_Trace_h
#define stf_util_Trace_h

#include "Ostream.h"
#include "../datatype/String.h"

namespace stf { 
namespace util {

//! 標準出力のラッパ．
/*! 
	@tparam T STFの内部状態を外部ファイルに書き出すためのトレースオブジェクト．
          種別ごとにデバッグ出力のオン・オフが選択できる．
          デフォルトでは全てのログ出力が無効化されているので，main関数などで
          必要なデバッグログに対応するTraceIdをenable関数で有効化する．
          出力先はOstream::clogの定義に依存する．

		使用側は必要な関数スコープでTraceオブジェクトをインスタンス化し，
		さらに途中で重要なイベントがあれば追加で記録する．
		スコープを抜けるとともにデストラクタが呼ばれ，スコープでの記録が完了する．

　	@code
	ModeManager::run(){
		util::Trace trace(util::Trace::kManager, "run ModeManager");
		...
		trace.debug("some more information");
		...
	}
	@endcode

	@code
	int main(void){
		stf::util::Trace::enable(stf::util::Trace::kManager); //機能マネージャに関するトレースログを有効化
		stf::util::Trace::enable(stf::util::Trace::kControlBlock); //姿勢制御ブロックに関するトレースログを有効化
		//それ以外のログは取らない
	}
	@endcode
*/
class Trace {
public:
	//! トレースログの種類を識別するための列挙体．
	enum TraceId{
		kManager = 0,//!< 機能マネージャ
		kControlBlock = 1,//!< 姿勢制御ブロック
		kCommand = 2,//!< コマンド処理
		kDataPool = 3,//!< データプール書き込み
		kEvent = 4,//!< イベント
	};

	//! コンストラクタ．
	/*!
		@param id   記録するトレースの種類．
		@param name トレースの名前．（関数名など）
	*/
	Trace(TraceId id, const char* name) : function_name_(name), id_(-1){
		if(this->active_table_[id]){
			id_ = id;
			util::clog << id_ << ",begin," << name << util::endl;
		}
	}

	//! コンストラクタ．
	/*!
		@param id   記録するトレースの種類．
		@param name トレースの名前．（関数名など）
	*/
	Trace(TraceId id, const datatype::String& name) : function_name_(0), id_(-1){
		if(this->active_table_[id]){
			id_ = id;
			function_name_ = name.to_char();
			util::clog << id_ << ",begin," << name << util::endl;
		}
	}

	~Trace() {
		if(id_ != -1){
			util::clog << id_ << ",end," << function_name_ << util::endl;
		}
	}

	//! 関数内部で生じたイベントのログ．
	/*!
		@param message 追加で記録する処理の名称．
	*/
	template<typename T>
	void debug(T message){
		if(id_ != -1){
			util::clog << id_ << ",do," << message << util::endl;
		}
	}
		
	//! 関数内部で生じたイベントのログ．
	/*!
		@param message 追加で記録する処理の名称．
	*/
	void debug(const datatype::String& message){
		if(id_ != -1){
			util::clog << id_ << ",do," << message.to_char() << util::endl;
		}
	}

	//! トレースフラグの有効化．この関数で明示的に有効化しないフラグはすべて無効．
	/*!
		@param id 有効化するトレースの種別．
	*/
	static void enable(TraceId id){
		active_table_[id] = true;
	}
private:
	static bool active_table_[5];
	int id_;
	const char* function_name_;
};



} /* End of namespace stf::util */
} /* End of namespace stf */

#endif // stf_util_Trace_h
