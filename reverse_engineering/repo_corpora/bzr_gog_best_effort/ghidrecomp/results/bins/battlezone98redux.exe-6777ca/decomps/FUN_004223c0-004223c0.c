
void * __thiscall FUN_004223c0(void *param_1,uint param_2)

{
  FUN_00420f50();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

