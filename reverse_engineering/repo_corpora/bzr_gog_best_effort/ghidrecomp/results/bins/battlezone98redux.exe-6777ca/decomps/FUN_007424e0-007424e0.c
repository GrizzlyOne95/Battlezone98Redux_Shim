
undefined4 FUN_007424e0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  FID_conflict_begin(local_c);
  while( true ) {
    cVar1 = FUN_00420f10(local_c);
    if (cVar1 == '\0') {
      return 0;
    }
    uVar2 = param_2;
    FUN_0042da60(param_2);
    cVar1 = FUN_0056f780(uVar2);
    if (cVar1 != '\0') break;
    FUN_0042da80();
  }
  uVar2 = FUN_0042de50();
  return uVar2;
}

