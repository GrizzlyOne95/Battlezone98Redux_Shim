
void * __thiscall FUN_005cf090(void *param_1,uint param_2)

{
  FUN_005cf0c0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

