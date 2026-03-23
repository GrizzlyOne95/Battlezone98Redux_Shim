
void * __thiscall FUN_005f69f0(void *param_1,uint param_2)

{
  FUN_005f7c00();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

