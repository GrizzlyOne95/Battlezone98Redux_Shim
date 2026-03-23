
void * __thiscall FUN_004f6810(void *param_1,uint param_2)

{
  FUN_004f6840();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

