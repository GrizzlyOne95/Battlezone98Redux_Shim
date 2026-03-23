
void * __thiscall FUN_007a0f80(void *param_1,uint param_2)

{
  FUN_007a0fb0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

