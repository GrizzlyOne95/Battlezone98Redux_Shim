
void * __thiscall FUN_005df310(void *param_1,uint param_2)

{
  FUN_005df5b0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

