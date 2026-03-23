
void * __thiscall FUN_00477d20(void *param_1,uint param_2)

{
  FUN_00477fb0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

