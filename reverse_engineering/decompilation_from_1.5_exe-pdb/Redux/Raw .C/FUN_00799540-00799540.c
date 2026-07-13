
void * __thiscall FUN_00799540(void *param_1,uint param_2)

{
  FUN_00799570();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

