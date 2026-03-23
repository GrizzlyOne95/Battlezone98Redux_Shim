
undefined4 FUN_00746720(short param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_14 [8];
  int local_c;
  undefined1 local_8 [4];
  
  local_c = FUN_0056f900();
  if (local_c != 0) {
    FUN_0042d8c0(local_8);
    FID_conflict_begin(local_14);
    while (cVar1 = FUN_00420f10(local_14), cVar1 != '\0') {
      iVar2 = FUN_0042da60();
      if (*(short *)(iVar2 + 0x28) == param_1) {
        uVar3 = FUN_0042de50();
        return uVar3;
      }
      FUN_0042da80();
    }
  }
  return 0;
}

