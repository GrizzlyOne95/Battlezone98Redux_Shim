
void __thiscall
FUN_004f3d40(int param_1,char *param_2,undefined4 param_3,float param_4,char *param_5)

{
  char *_Str1;
  char cVar1;
  int iVar2;
  size_t _Size;
  void *pvVar3;
  float10 fVar4;
  float fVar5;
  int local_14;
  char *local_10;
  
  local_14 = 0;
  while( true ) {
    if (*(int *)(param_1 + 8) <= local_14) {
      return;
    }
    _Str1 = (char *)(param_1 + 0xc + local_14 * 0x18);
    iVar2 = _strnicmp(_Str1,param_2,0x10);
    if (iVar2 == 0) break;
    local_14 = local_14 + 1;
  }
  if (param_5 != (char *)0x0) {
    local_10 = param_5;
    do {
      cVar1 = *local_10;
      local_10 = local_10 + 1;
    } while (cVar1 != '\0');
    _Size = (int)local_10 - (int)(param_5 + 1);
    free(*(void **)(_Str1 + 0x10));
    pvVar3 = malloc(_Size + 1);
    *(void **)(_Str1 + 0x10) = pvVar3;
    memcpy(*(void **)(_Str1 + 0x10),param_5,_Size);
    *(undefined1 *)(*(int *)(_Str1 + 0x10) + _Size) = 0;
  }
  *(undefined4 *)(_Str1 + 0x14) = param_3;
  fVar4 = (float10)FUN_00822da0();
  fVar5 = (float)fVar4 + param_4;
  if ((0.0 < param_4) &&
     (*(float *)(param_1 + 0xfc) <= fVar5 && fVar5 != *(float *)(param_1 + 0xfc))) {
    *(float *)(param_1 + 0xfc) = fVar5;
  }
  return;
}

