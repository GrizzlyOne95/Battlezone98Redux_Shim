
void * __thiscall FUN_004e1cc0(void *param_1,uint param_2)

{
  FUN_004e2420();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

