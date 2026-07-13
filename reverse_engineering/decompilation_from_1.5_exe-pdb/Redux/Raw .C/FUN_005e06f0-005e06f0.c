
void * __thiscall FUN_005e06f0(void *param_1,uint param_2)

{
  FUN_005e0720();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

