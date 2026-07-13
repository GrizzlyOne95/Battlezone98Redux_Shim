
void * __thiscall FUN_00804f60(void *param_1,uint param_2)

{
  FUN_00804ff0();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

