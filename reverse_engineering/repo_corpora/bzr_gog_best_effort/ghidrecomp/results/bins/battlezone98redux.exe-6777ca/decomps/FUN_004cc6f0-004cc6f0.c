
void FUN_004cc6f0(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int local_10;
  undefined4 *local_c;
  undefined1 local_8 [4];
  
  if (DAT_00917a5c != 0) {
    FUN_0042d8c0(local_8);
    while( true ) {
      uVar2 = FID_conflict_begin(local_18);
      cVar1 = FUN_00420f10(uVar2);
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_0042de50();
      local_c = (undefined4 *)*piVar3;
      if (local_c[1] != 0) {
        local_10 = FUN_004cca70(local_c[1]);
        if (local_10 != 0) {
          *(int *)*local_c = local_10;
        }
      }
      FUN_00438c10(local_14,0);
    }
  }
  return;
}

