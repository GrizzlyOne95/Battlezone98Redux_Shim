
CAtlBaseModule * __thiscall FUN_0081bae0(CAtlBaseModule *param_1,uint param_2)

{
  ATL::CAtlBaseModule::~CAtlBaseModule(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

