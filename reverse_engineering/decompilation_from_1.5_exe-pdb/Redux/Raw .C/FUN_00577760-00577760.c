
uint FUN_00577760(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int local_14;
  int local_10;
  uint local_c;
  undefined4 local_8;
  
  FUN_00430590();
  local_c = 0;
  puVar2 = (undefined4 *)FUN_00420260(local_18);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_20);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_00423870();
    if ((*(int *)(iVar4 + 0x10) == 0) ||
       (iVar4 = FUN_00423870(), *(short *)(*(int *)(iVar4 + 0x10) + 0x28) == DAT_009180d4)) {
      local_c = local_c + 1;
    }
    else {
      iVar4 = FUN_00423870();
      local_10 = *(int *)(iVar4 + 0x10);
      if (*(int *)(local_10 + 0x60) != 0 || *(int *)(local_10 + 100) != 0) {
        iVar4 = FUN_00423870();
        local_14 = *(int *)(iVar4 + 0x10);
        if (*(int *)(local_14 + 0x58) != 0 || *(int *)(local_14 + 0x5c) != 0) {
          local_c = local_c + 1;
        }
      }
    }
    FUN_004305b0(local_1c,0);
  }
  return local_c & 0xffff;
}

