
void * __thiscall FUN_005a2b10(void *param_1,uint param_2)

{
  FUN_005a3730();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

