
void FUN_005769d0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_00420260(local_c);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_14);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    iVar4 = FUN_00423870();
    if (*(int *)(iVar4 + 0x10) != 0) {
      iVar4 = FUN_00423870();
      if (**(char **)(iVar4 + 0x10) != '\0') {
        iVar4 = FUN_00423870();
        if (*(short *)(*(int *)(iVar4 + 0x10) + 0x28) != DAT_009180d4) {
          FUN_00422150();
          FUN_00576390();
        }
      }
    }
    FUN_004305b0(local_10,0);
  }
  return;
}

