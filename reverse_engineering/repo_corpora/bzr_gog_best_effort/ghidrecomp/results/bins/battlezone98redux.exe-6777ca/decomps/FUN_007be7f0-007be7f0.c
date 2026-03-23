
void * __thiscall FUN_007be7f0(void *param_1,uint param_2)

{
  FUN_007be820();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

