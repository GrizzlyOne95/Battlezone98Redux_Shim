
void * __thiscall FUN_004d26e0(void *param_1,uint param_2)

{
  FUN_004d2710();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

