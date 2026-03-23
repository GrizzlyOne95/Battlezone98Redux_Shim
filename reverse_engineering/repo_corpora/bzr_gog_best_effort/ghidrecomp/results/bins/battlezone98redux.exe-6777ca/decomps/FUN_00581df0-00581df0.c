
void * __thiscall FUN_00581df0(void *param_1,uint param_2)

{
  FUN_00581e20();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

