
void FUN_0074e230(void)

{
  int *piVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  uint uStack_15c;
  char *local_6c;
  undefined1 local_60 [72];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bed3;
  local_10 = ExceptionList;
  uStack_15c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_15c;
  ExceptionList = &local_10;
  local_18 = uStack_15c;
  basic_string<>();
  local_8 = 1;
  piVar1 = (int *)FUN_0073ae00();
  if (piVar1 != (int *)0x0) {
    FUN_0073a9b0(&stack0xfffffe9c);
    pcVar2 = (char *)(**(code **)(*piVar1 + 0x14))();
    if ((pcVar2 != (char *)0x0) && (*pcVar2 != '\0')) {
      FUN_0073bf60();
      FUN_0045e0f0();
      ~basic_string<>();
      pcVar2 = (char *)FUN_0041f870();
      pcVar3 = strrchr(pcVar2,0x2e);
      local_6c = pcVar3;
      if (pcVar3 != (char *)0x0) {
        do {
          local_6c = local_6c + 1;
          if (*local_6c == '\0') break;
          iVar4 = isdigit((int)*local_6c);
        } while (iVar4 != 0);
        if ((*local_6c == '\0') && ((uint)((int)pcVar3 - (int)pcVar2) < 0x400)) {
          FUN_0045e1d0(local_60);
          FUN_0045e0f0();
          ~basic_string<>();
        }
      }
    }
  }
  FUN_0074e4a4();
  return;
}

