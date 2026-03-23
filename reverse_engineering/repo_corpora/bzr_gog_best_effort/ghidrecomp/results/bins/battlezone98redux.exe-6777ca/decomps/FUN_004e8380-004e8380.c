
void * __thiscall FUN_004e8380(void *param_1,uint param_2)

{
  FUN_004e83b0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

