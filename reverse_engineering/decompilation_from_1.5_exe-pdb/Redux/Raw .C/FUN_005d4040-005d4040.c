
void * __thiscall FUN_005d4040(void *param_1,uint param_2)

{
  FUN_005d4120();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

