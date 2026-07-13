
undefined4 FUN_004d3540(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int *local_10;
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_18);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      return 0;
    }
    local_10 = (int *)FUN_0042de50();
    if (*local_10 == param_1) break;
    FUN_00438c10(local_14,0);
  }
  return 1;
}

