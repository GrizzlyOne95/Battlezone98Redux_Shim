
void * __thiscall FUN_006e43c0(void *param_1,uint param_2)

{
  FUN_006e4590();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

