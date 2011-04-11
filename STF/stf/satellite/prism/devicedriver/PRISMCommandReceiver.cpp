/**
 * @file   PRISMCommandReceiver.cpp
 * @brief  
 *
 * @author Taiga Nomi
 * @date   2011.02.16
 */
#include "PRISMCommandReceiver.h"
#include "../../../core/command/Includes.h"
#include "../factory/PRISMGlobal.h"

namespace stf {
namespace core {
namespace devicedriver {
namespace cmhandler {

namespace {

int strcmp(const char *s1, const char *s2)
{
  register const unsigned char *ss1, *ss2;
  for (ss1 = (const unsigned char*)s1, ss2 = (const unsigned char*)s2;
       *ss1 == *ss2 && *ss1 != '\0';
       ss1++, ss2++)
    ;
  return *ss1 - *ss2;
}

}


//デバッグ用の特殊化．外部ファイルから1行ずつ読み込み，
template<> void PRISMCommandReceiver<environment::Simulator<app::PRISM> >::receive_command(){
	std::string line;



	if(this->ifs_ != 0 && !this->ifs_->eof()){
//		this->ifs_->getline(line);
		
	}

}

template<>
core::command::Command* __prism_powercmd_analyze<environment::Simulator<app::PRISM> >(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<environment::Simulator<app::PRISM> >* g){
	if(strcmp(cmd, "pu") == 0)
	{
		command::Command* c = g->pr_c_pu->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "pd") == 0)
	{
		command::Command* c = g->pr_c_pd->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "mds") == 0)
	{
		return g->pr_c_mds->clone(t);
	}
	if(strcmp(cmd, "mdn") == 0)
	{
		return g->pr_c_mdn->clone(t);
	}

	if(strcmp(cmd, "md") == 0)
	{
		return g->pr_c_md->clone(t);
	}

	if(strcmp(cmd, "hth") == 0)
	{
		return g->pr_c_hth->clone(t);
	}
	if(strcmp(cmd, "hdt") == 0)
	{
		command::Command* c = g->pr_c_hdt->clone(t);
		c->init(params, paramlength);
		return c;
	}
	return 0;
}


template<>
core::command::Command* __prism_cdhcmd_analyze<environment::Simulator<app::PRISM> >(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<environment::Simulator<app::PRISM> >* g){
	if(strcmp(cmd, "alv") == 0)
	{
		return g->pr_c_alv->clone(t);
	}
	if(strcmp(cmd, "hta") == 0)
	{
		return g->pr_c_hta->clone(t);
	}
	if(strcmp(cmd, "htd") == 0)
	{
		return g->pr_c_htd->clone(t);
	}
	if(strcmp(cmd, "htg") == 0)
	{
		return g->pr_c_htd->clone(t);
	}
	if(strcmp(cmd, "hts") == 0)
	{
		command::Command* c = g->pr_c_htd->clone(t);
		c->init(params, paramlength);
		return c;
	}

	if(strcmp(cmd, "rtg") == 0)
	{
		return g->pr_c_rtg->clone(t);
	}
	if(strcmp(cmd, "rts") == 0)
	{
		command::Command* c = g->pr_c_rts->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "tmg") == 0)
	{
		return g->pr_c_tmg->clone(t);
	}
	if(strcmp(cmd, "tms") == 0)
	{
		command::Command* c = g->pr_c_tms->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "tlg") == 0)
	{
		return g->pr_c_tlg->clone(t);
	}
	if(strcmp(cmd, "tos") == 0)
	{
		command::Command* c = g->pr_c_tos->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "trs") == 0)
	{
		command::Command* c = g->pr_c_trs->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "tss") == 0)
	{
		return g->pr_c_tss->clone(t);
	}
	if(strcmp(cmd, "sgs") == 0)
	{
		return g->pr_c_sgs->clone(t);
	}
	return 0;
}

template<>
core::command::Command* __prism_adcscmd_analyze<environment::Simulator<app::PRISM> >(char* cmd, int* params, int paramlength, const datatype::Time& t, const stf::PRISMGlobal<environment::Simulator<app::PRISM> >* g){
	if(strcmp(cmd, "aen") == 0)
	{
		if(params[0] == 0){
			return g->pr_c_aen0->clone(t);
		}
		else{
			return g->pr_c_aen1->clone(t);
		}
	}
	if(strcmp(cmd, "ams") == 0)
	{
		command::Command* c = g->pr_c_ams->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "amG") == 0)
	{
		return g->pr_c_amG->clone(t);
	}
	if(strcmp(cmd, "apg") == 0)
	{
		return g->pr_c_apg->clone(t);
	}
	if(strcmp(cmd, "atw") == 0)
	{
		command::Command* c = g->pr_c_atw->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "atr") == 0)
	{
		command::Command* c = g->pr_c_atr->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "ato") == 0)
	{
		command::Command* c = g->pr_c_ato->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "aps") == 0)
	{
		command::Command* c = g->pr_c_aps->clone(t);
		c->init(params, paramlength);
		return c;
	}
	if(strcmp(cmd, "apg") == 0)
	{
		return g->pr_c_apg->clone(t);
	}
	return 0;
}

} /* End of namespace stf::core::devicedriver::cmhandler */
} /* End of namespace stf::core::devicedriver */
} /* End of namespace stf::core */
} /* End of namespace stf */

