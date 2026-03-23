
void __thiscall FUN_004f3e70(int param_1,char *param_2)

{
  char *_Str1;
  undefined4 *puVar1;
  int iVar2;
  int local_c;
  
  local_c = 0;
  while( true ) {
    if (*(int *)(param_1 + 8) <= local_c) {
      return;
    }
    _Str1 = (char *)(param_1 + 0xc + local_c * 0x18);
    iVar2 = _strnicmp(_Str1,param_2,0x10);
    if (iVar2 == 0) break;
    local_c = local_c + 1;
  }
  if (*(int *)(_Str1 + 0x10) != 0) {
    free(*(void **)(_Str1 + 0x10));
    _Str1[0x10] = '\0';
    _Str1[0x11] = '\0';
    _Str1[0x12] = '\0';
    _Str1[0x13] = '\0';
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  if (local_c < *(int *)(param_1 + 8)) {
    memmove((void *)(param_1 + 0xc + local_c * 0x18),(void *)(param_1 + 0x24 + local_c * 0x18),
            (*(int *)(param_1 + 8) - local_c) * 0x18);
  }
  puVar1 = (undefined4 *)(param_1 + 0xc + *(int *)(param_1 + 8) * 0x18);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  return;
}

