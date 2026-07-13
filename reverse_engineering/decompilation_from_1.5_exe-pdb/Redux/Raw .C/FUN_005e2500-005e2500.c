
void * __thiscall FUN_005e2500(void *param_1,uint param_2)

{
  FUN_005e25f0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

