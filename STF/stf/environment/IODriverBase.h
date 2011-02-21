/**
 * @file   IODriverBase.h
 * @brief  環境クラス共通の基底IOドライバ．
 *         各環境クラスにおけるIOはこの基底ドライバを使用するか，ここから派生させることを基本とする．
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_environment_IODriverBase_h
#define stf_environment_IODriverBase_h

#include "../Macros.h"

namespace stf {
namespace environment {

//! 基底GPIOドライバ．
/*! 
	入出力を表すstateと，IO状態を表すdataを持つ．
	いずれもunsigned intで表現しているので，コンパイル環境における
	unsigned intのビット数を超えるチャネルのGPIOは取り扱うことができない．
	@tparam i GPIOのチャネル数．
*/
template<int i>class GPIOBase {
public:
	GPIOBase(){}
	explicit GPIOBase(int base_addr): base_addr_(base_addr){}
	virtual ~GPIOBase(){}
	void set_state(unsigned int state){ state_ = state;}
	void set_data(unsigned int data){ data_ = data;}
	unsigned int get_state() const { return state_; }
	unsigned int get_data() const { return data_; }
	void set_data_at(int i, unsigned char state){
		if(state) data_ |= (0x00000001 << i);
		else data_ &= ~(0x00000001 << i);
	}
	bool operator [](int i) const { 
		if((0x00000001 << i) & data_) return true;
		else return false;
	}
private:
	int base_addr_;
	unsigned int data_;
	unsigned int state_;
};

//! 基底SPIドライバ．
/*! */
class SPIBase {
public:
	SPIBase(){}
	explicit SPIBase(int base_addr): base_addr_(base_addr){}
	virtual ~SPIBase(){}
	virtual char putchar(char i){}
	virtual char getchar(){ return 0; }
	virtual unsigned int putint(unsigned int i){}
	virtual unsigned int getint() { return 0; }
	virtual void init(){}
	virtual bool clear_rx_buffer(){ return true; }
	virtual bool clear_tx_buffer(){ return true; }
	virtual bool is_tx_buffer_full(){ return false; }
	virtual bool is_rx_buffer_full(){ return false; }
private:
	DISALLOW_COPY_AND_ASSIGN(SPIBase);
	int base_addr_;
};

//! 基底UARTドライバ．
/*! */
class UARTBase {
public:
	UARTBase(){}
	explicit UARTBase(int base_addr) : base_addr_(base_addr){}
	virtual ~UARTBase(){}
	virtual char putchar(char i){}
	virtual char getchar(){ return 0; }
	virtual unsigned int putint(unsigned int i){}
	virtual unsigned int getint() { return 0; }
	virtual void init(){}
	virtual bool clear_rx_buffer(){ return true; }
	virtual bool clear_tx_buffer(){ return true; }
	virtual bool is_tx_buffer_full(){ return false; }
	virtual bool is_rx_buffer_full(){ return false; }
private:
	DISALLOW_COPY_AND_ASSIGN(UARTBase);
	int base_addr_;
};

} /* End of namespace stf::environment */
} /* End of namespace stf */

#endif // stf_environment_IODriverBase_h
