
void * __thiscall FUN_00528aa0(void *param_1,uint param_2)

{
  FUN_00528ad0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

