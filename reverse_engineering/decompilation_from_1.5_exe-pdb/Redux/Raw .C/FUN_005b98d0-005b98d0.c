
void * __thiscall FUN_005b98d0(void *param_1,uint param_2)

{
  FUN_005b9a40();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

