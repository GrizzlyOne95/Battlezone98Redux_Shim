
void * __thiscall FUN_00676dd0(void *param_1,uint param_2)

{
  FUN_00430250();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

