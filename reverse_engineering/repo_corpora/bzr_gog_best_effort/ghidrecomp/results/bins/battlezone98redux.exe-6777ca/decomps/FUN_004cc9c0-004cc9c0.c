
void FUN_004cc9c0(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [8];
  int local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_28);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_0042de50();
    local_14 = *piVar3;
    local_c = local_14;
    if (local_14 == 0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_004cc8b0(1);
    }
    FUN_00438c10(local_24,0);
  }
  local_1c = DAT_00917a54;
  local_10 = DAT_00917a54;
  if (DAT_00917a54 != 0) {
    FUN_004cc8e0(1);
  }
  DAT_00917a54 = 0;
  return;
}

