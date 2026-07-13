
void * __thiscall FUN_004f2a70(void *param_1,uint param_2)

{
  FUN_004f2ad0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

