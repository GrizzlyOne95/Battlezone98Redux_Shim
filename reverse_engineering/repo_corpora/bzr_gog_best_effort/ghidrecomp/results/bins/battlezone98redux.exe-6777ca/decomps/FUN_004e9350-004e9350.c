
void * __thiscall FUN_004e9350(void *param_1,uint param_2)

{
  FUN_004e9440();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

