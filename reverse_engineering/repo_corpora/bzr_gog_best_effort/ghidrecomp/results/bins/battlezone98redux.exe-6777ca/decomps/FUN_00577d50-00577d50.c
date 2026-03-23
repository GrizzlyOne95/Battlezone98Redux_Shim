
bool FUN_00577d50(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined1 local_1c [8];
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_8 [4];
  
  local_c = 0;
  if (DAT_00917f8e == '\0') {
    bVar4 = false;
  }
  else {
    FUN_00420260(local_8);
    FID_conflict_begin(local_1c);
    while (cVar1 = FUN_00420f10(local_1c), cVar1 != '\0') {
      iVar2 = FUN_00422150();
      uVar5 = *(undefined4 *)(iVar2 + 0x10);
      local_10 = FUN_00575510(0x13);
      local_14 = DAT_00917fa4;
      iVar2 = FUN_004bb390(uVar5);
      if (iVar2 == 4) {
        piVar3 = (int *)get();
        local_14 = *piVar3;
      }
      if (0 < local_14) {
        local_c = local_c + 1;
      }
      FUN_00428570();
    }
    bVar4 = local_c == 1;
  }
  return bVar4;
}

