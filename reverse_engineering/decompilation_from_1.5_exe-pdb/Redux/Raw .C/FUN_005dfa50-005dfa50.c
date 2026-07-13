
void * __thiscall FUN_005dfa50(void *param_1,uint param_2)

{
  FUN_005dfa80();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

