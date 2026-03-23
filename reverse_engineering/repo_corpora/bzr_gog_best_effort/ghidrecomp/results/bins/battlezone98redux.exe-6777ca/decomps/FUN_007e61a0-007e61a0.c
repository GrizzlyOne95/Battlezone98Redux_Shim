
void * __thiscall FUN_007e61a0(void *param_1,uint param_2)

{
  FUN_007dba90();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

