
void * __thiscall FUN_005e7800(void *param_1,uint param_2)

{
  FUN_005e7830();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

