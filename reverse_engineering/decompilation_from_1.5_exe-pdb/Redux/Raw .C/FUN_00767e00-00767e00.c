
void * __thiscall FUN_00767e00(void *param_1,uint param_2)

{
  FUN_00767e30();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

