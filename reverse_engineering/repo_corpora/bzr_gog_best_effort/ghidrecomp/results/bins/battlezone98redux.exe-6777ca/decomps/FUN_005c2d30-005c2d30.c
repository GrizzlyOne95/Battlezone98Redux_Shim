
void * __thiscall FUN_005c2d30(void *param_1,uint param_2)

{
  FUN_005c2fe0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

