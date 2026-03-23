
exception * __thiscall FUN_006a82d0(exception *param_1,uint param_2)

{
  exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

