
void * __thiscall FUN_00676da0(void *param_1,uint param_2)

{
  FUN_00667da0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

