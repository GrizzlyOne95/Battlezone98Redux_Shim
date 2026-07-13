
undefined4 FUN_00746690(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_14 [8];
  int local_c;
  undefined1 local_8 [4];
  
  local_c = FUN_0056f900();
  if (local_c != 0) {
    FUN_0042d8c0(local_8);
    FID_conflict_begin(local_14);
    while (cVar1 = FUN_00420f10(local_14), cVar1 != '\0') {
      uVar2 = param_1;
      FUN_0042da60(param_1);
      cVar1 = FUN_0056f780(uVar2);
      if (cVar1 != '\0') {
        uVar2 = FUN_0042de50();
        return uVar2;
      }
      FUN_0042da80();
    }
  }
  return 0;
}

