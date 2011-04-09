/**
 * @file   PRISMCustomManager.h
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#ifndef stf_core_manager_PRISMCustomManager_h
#define stf_core_manager_PRISMCustomManager_h

#include "../../../core/manager/CustomManagerBase.h"
#include "../devicedriver/PRISMADC.h"
namespace stf {
namespace core {
namespace manager {

template<class Env> class HeaterControl;

template <class Env>
class PRISMCustomManager : public CustomManagerBase
{
public:
	PRISMCustomManager( HeaterControl<Env>* control)
		: CustomManagerBase(), control_(control){}
	~PRISMCustomManager(){}
	virtual void run();
	virtual bool runnable();

private:
	HeaterControl<Env>* control_;
};

template<class Env>
void PRISMCustomManager<Env>::run(){
	this->control_->run();
}

template<class Env>
bool PRISMCustomManager<Env>::runnable(){
	return true;
}


template<class Env>
class HeaterControl {
public:
	HeaterControl(core::devicedriver::PRISMTempSensor<Env>* source, unsigned int channel, unsigned short ref)
		: enable_(false), source_(source), ref_(ref), channel_(channel) {}

	void enable(){ enable_ = true; }
	void disable(){ enable_ = false; }
	void run()
	{
		if(!enable_) return;
		datatype::Temperature value = (*(this->source_))[channel_];//§Œä‘ÎÛ‚Ì‰·“x‚ğæ“¾
			if(value < ref_){//‚ ‚é’l‚æ‚è¬‚³‚¯‚ê‚ÎON

			}else{//¬‚³‚¯‚ê‚ÎOFF

			}
	}
	datatype::String get_status() const{
		return "not implemented yet";
	}
	void set_params(int freq, int duty, int ref){
		freq_ = freq;
		duty_ = duty;
		ref_ = ref;
	}
private:
	int freq_;
	int duty_;
	datatype::Temperature ref_;
	const unsigned int channel_;
	bool enable_;
	core::devicedriver::PRISMTempSensor<Env>* source_;
};

} /* End of namespace stf::core::manager */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_manager_PRISMCustomManager_h