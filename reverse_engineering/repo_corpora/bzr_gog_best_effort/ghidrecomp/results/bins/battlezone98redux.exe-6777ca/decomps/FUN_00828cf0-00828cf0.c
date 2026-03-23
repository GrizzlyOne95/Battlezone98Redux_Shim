
char * FUN_00828cf0(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  char *_Str1;
  char *_Str2;
  size_t _MaxCount;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  if ((DAT_02cc3b68 & 1) == 0) {
    DAT_02cc3b68 = DAT_02cc3b68 | 1;
    FUN_008289d0(&DAT_02cc3b6c);
    FUN_0083e979(FUN_008681b0);
  }
  puVar2 = (undefined4 *)FUN_0042d8c0(local_10);
  local_8 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_14);
  local_c = *puVar2;
  cVar1 = FUN_00420f10(&local_c);
  if (cVar1 != '\0') {
    iVar3 = FUN_004305e0();
    _MaxCount = *(size_t *)(iVar3 + 0x18);
    _Str2 = param_1;
    FUN_004305e0();
    _Str1 = (char *)FUN_0041f870();
    iVar3 = strncmp(_Str1,_Str2,_MaxCount);
    if (iVar3 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
    iVar3 = FUN_004305e0();
    param_1 = param_1 + *(int *)(iVar3 + 0x18);
  }
  return param_1;
}

