
void * __thiscall FUN_007c43f0(void *param_1,uint param_2)

{
  FUN_007c4420();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

