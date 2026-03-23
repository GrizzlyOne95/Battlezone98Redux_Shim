
undefined1 FUN_00577e20(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined1 local_5;
  
  local_5 = 0;
  FUN_00420260(local_10);
  FID_conflict_begin(local_14);
  while( true ) {
    cVar1 = FUN_00420f10(local_14);
    if (cVar1 == '\0') break;
    iVar2 = FUN_00422150();
    local_c = *(int *)(iVar2 + 0x10);
    if ((local_c != 0) && (*(int *)(local_c + 0x50) == 0)) {
      uVar3 = FUN_00575510(0xd);
      iVar2 = FUN_004bb390(uVar3);
      if (iVar2 == 0x100) {
        local_5 = 1;
      }
    }
    FUN_00428570();
  }
  return local_5;
}

