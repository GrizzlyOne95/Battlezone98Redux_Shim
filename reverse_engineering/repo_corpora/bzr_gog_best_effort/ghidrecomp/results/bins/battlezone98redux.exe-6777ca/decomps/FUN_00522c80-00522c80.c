
void * __thiscall FUN_00522c80(void *param_1,uint param_2)

{
  FUN_00522cb0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

