
void * __thiscall FUN_004e7cc0(void *param_1,uint param_2)

{
  FUN_004e7cf0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

