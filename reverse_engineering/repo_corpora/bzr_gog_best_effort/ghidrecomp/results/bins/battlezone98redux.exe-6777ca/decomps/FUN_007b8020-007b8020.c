
void * __thiscall FUN_007b8020(void *param_1,uint param_2)

{
  FUN_007b8050();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

