
void * __thiscall FUN_006584a0(void *param_1,uint param_2)

{
  FUN_006584d0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

