
void * FUN_008273e0(undefined4 *param_1,undefined4 param_2,size_t *param_3,void *param_4,int param_5
                   )

{
  size_t _Size;
  int iVar1;
  size_t sVar2;
  bool bVar3;
  void *local_1c;
  void *local_c;
  void *local_8;
  
  local_8 = (void *)0x0;
  iVar1 = FUN_00827330(param_1,param_2);
  _Size = *(size_t *)(iVar1 + 0x18);
  bVar3 = (*(uint *)(iVar1 + 0x20) & 6) != 0;
  if ((bVar3) || (param_4 == (void *)0x0)) {
    local_c = malloc(_Size);
    local_8 = local_c;
  }
  else {
    if (param_5 < (int)_Size) {
      return (void *)0x0;
    }
    local_c = param_4;
  }
  fseek((FILE *)*param_1,*(long *)(iVar1 + 0x10),0);
  sVar2 = fread(local_c,_Size,1,(FILE *)*param_1);
  if (sVar2 == 0) {
    sprintf(&DAT_009467c0,"Could not read record %s from file \"%s\"",param_2,param_1 + 1);
    if (local_8 != (void *)0x0) {
      free(local_8);
    }
    local_c = (void *)0x0;
  }
  else {
    if (bVar3) {
      sVar2 = *(int *)(iVar1 + 0x20) >> 8;
      if (param_4 == (void *)0x0) {
        local_1c = malloc(sVar2);
      }
      else {
        if (param_5 < (int)sVar2) {
          free(local_8);
          return (void *)0x0;
        }
        local_1c = param_4;
      }
      iVar1 = FUN_008249a0(local_c,_Size,*(undefined4 *)(iVar1 + 0x20),local_1c,sVar2);
      free(local_8);
      if (iVar1 == 0) {
        return (void *)0x0;
      }
      local_c = local_1c;
      *param_3 = sVar2;
    }
    else {
      *param_3 = _Size;
    }
    if (param_1[7] != 0) {
      FUN_00826bf0(local_c,*param_3,param_1[7]);
    }
  }
  return local_c;
}

