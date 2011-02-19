#ifndef stf_core_functor_OutputFunctor_h
#define stf_core_functor_OutputFunctor_h


namespace stf {
namespace core {
namespace manager {
class ModeManager;
}
namespace mode {
class ModeBase;
}
namespace functor {

struct MSG {
	void operator()() const ;
private:
	//DISALLOW_COPY_AND_ASSIGN(MSG);
};

struct ModeChangeFunc{
	ModeChangeFunc(core::manager::ModeManager* modeman, const core::mode::ModeBase& next) : next_(next), modeman_(modeman){}
	int operator()() const;
private:
	const core::mode::ModeBase& next_;
	core::manager::ModeManager* modeman_;
};

} /* End of namespace stf::core::fuctor */
} /* End of namespace stf::core */
} /* End of namespace stf */

#endif // stf_core_functor_OutputFunctor_h
