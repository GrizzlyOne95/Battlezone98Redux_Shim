
void * __thiscall FUN_005d7320(void *param_1,uint param_2)

{
  FUN_005d7350();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

