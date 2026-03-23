
void * __thiscall FUN_006e4560(void *param_1,uint param_2)

{
  FUN_006e45d0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

