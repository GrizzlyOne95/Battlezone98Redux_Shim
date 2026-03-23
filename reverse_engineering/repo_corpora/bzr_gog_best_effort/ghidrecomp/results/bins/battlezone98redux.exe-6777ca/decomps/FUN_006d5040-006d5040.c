
void * __thiscall FUN_006d5040(void *param_1,uint param_2)

{
  FUN_006d4ea0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

