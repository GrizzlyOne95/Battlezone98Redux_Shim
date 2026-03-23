
undefined4 FUN_005776c0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined4 local_8;
  
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_00420260(local_10);
  local_8 = *puVar2;
  do {
    uVar3 = FID_conflict_begin(local_18);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      return 1;
    }
    iVar4 = FUN_00423870();
    if ((*(int *)(iVar4 + 0x10) != 0) &&
       (iVar4 = FUN_00423870(), *(short *)(*(int *)(iVar4 + 0x10) + 0x28) != DAT_009180d4)) {
      iVar4 = FUN_00423870();
      local_c = *(int *)(iVar4 + 0x10);
      if (*(int *)(local_c + 0x58) == 0 && *(int *)(local_c + 0x5c) == 0) {
        return 0;
      }
    }
    FUN_004305b0(local_14,0);
  } while( true );
}

