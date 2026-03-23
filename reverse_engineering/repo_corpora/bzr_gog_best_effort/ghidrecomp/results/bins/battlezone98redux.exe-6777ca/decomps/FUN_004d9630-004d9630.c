
void __thiscall FUN_004d9630(int param_1,char *param_2)

{
  char cVar1;
  void *_Dst;
  char *local_c;
  
  if (*(int *)(param_1 + 0x100) != 0) {
    operator_delete__(*(void **)(param_1 + 0x100));
  }
  local_c = param_2;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  _Dst = (void *)FUN_0083d92c(local_c + (1 - (int)(param_2 + 1)));
  memcpy(_Dst,param_2,(size_t)(local_c + (1 - (int)(param_2 + 1))));
  *(void **)(param_1 + 0x100) = _Dst;
  return;
}

