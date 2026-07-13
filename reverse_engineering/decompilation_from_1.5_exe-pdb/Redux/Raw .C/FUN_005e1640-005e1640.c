
void * __thiscall FUN_005e1640(void *param_1,uint param_2)

{
  FUN_005e1670();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

