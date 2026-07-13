
void * __thiscall FUN_006e6ad0(void *param_1,uint param_2)

{
  FUN_006e6a60();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

