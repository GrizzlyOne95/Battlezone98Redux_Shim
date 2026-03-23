
char FUN_00577840(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  uint local_10;
  undefined4 local_c;
  char local_5;
  
  FUN_00430590();
  local_5 = '\0';
  local_10 = FUN_00822e60();
  puVar2 = (undefined4 *)FUN_00420260(local_14);
  local_c = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_1c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_00423870();
    if ((*(int *)(iVar4 + 0x10) == 0) ||
       (iVar4 = FUN_00423870(), *(short *)(*(int *)(iVar4 + 0x10) + 0x28) == DAT_009180d4)) {
      local_5 = local_5 + '\x01';
    }
    else {
      iVar4 = FUN_00423870();
      if (local_10 < *(int *)(*(int *)(iVar4 + 0x10) + 0x48) + 60000U) {
        local_5 = local_5 + '\x01';
      }
    }
    FUN_004305b0(local_18,0);
  }
  return local_5;
}

