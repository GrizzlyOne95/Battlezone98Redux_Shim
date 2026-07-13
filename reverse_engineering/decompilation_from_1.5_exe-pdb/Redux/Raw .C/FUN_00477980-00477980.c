
undefined4 FUN_00477980(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int *local_14;
  undefined4 local_10 [2];
  undefined4 local_8;
  
  FID_conflict_begin(local_10);
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_18);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_20);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      return 0;
    }
    local_14 = (int *)FUN_0042de50();
    if (*local_14 == param_1) break;
    local_10[0] = local_8;
    FUN_00438c10(local_1c,0);
  }
  uVar3 = FID_conflict_begin(local_24);
  cVar1 = FUN_004221b0(uVar3);
  if (cVar1 != '\0') {
    return 0;
  }
  uVar3 = FUN_0042de50();
  return uVar3;
}

