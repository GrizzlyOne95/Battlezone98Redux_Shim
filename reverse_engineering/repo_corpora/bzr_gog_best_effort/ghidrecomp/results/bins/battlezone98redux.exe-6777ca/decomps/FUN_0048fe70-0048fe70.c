
void * __thiscall FUN_0048fe70(void *param_1,uint param_2)

{
  FUN_0048fea0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

