
void * __thiscall FUN_004d2ae0(void *param_1,uint param_2)

{
  FUN_004d2c90();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

