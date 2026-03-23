
void * __thiscall FUN_006ac5b0(void *param_1,uint param_2)

{
  FUN_006ac550();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

