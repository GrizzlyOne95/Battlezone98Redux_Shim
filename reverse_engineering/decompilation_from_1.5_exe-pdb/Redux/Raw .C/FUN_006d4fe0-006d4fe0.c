
void * __thiscall FUN_006d4fe0(void *param_1,uint param_2)

{
  FUN_006d4d50();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

