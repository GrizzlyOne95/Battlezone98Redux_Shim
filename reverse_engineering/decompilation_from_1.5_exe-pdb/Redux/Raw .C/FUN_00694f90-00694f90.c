
void * __thiscall FUN_00694f90(void *param_1,uint param_2)

{
  FUN_0069d880();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

