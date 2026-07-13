
undefined4 FUN_0041d100(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FID_conflict_begin(local_8);
  FID_conflict_end(local_c);
  while( true ) {
    cVar1 = FID_conflict_operator__(local_c);
    if (cVar1 == '\0') {
      return 0;
    }
    uVar2 = FUN_004221e0(param_2);
    cVar1 = FUN_00427310(uVar2);
    if (cVar1 != '\0') break;
    FUN_00422200();
  }
  uVar2 = FUN_00421ec0();
  return uVar2;
}

