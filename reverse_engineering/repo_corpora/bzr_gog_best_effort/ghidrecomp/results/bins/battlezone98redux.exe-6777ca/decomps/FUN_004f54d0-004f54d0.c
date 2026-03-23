
void * __thiscall FUN_004f54d0(void *param_1,uint param_2)

{
  FUN_004f5500();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

