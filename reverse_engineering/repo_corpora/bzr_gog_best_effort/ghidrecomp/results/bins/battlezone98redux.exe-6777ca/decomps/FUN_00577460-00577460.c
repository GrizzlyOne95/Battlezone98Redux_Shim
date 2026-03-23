
void FUN_00577460(void)

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
  while( true ) {
    uVar3 = FID_conflict_begin(local_18);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_00423870();
    if (*(int *)(iVar4 + 0x10) != 0) {
      iVar4 = FUN_00423870();
      if (*(short *)(*(int *)(iVar4 + 0x10) + 0x28) != DAT_009180d4) {
        local_c = FUN_007659f0();
        if (local_c != 0) {
          iVar4 = FUN_00422150();
          FUN_007592a0(*(int *)(iVar4 + 0x10) + 0x30);
        }
      }
    }
    FUN_004305b0(local_14,0);
  }
  return;
}

