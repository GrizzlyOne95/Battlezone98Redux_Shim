
void * __thiscall FUN_006b7220(void *param_1,uint param_2)

{
  FUN_006b71e0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

