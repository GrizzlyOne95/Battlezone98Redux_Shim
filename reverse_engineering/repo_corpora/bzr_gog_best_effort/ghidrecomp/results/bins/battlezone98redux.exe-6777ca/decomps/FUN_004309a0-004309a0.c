
undefined4 FUN_004309a0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined1 local_30 [12];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  int local_1c;
  int local_18;
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_8 [4];
  
  FUN_00428a90();
  if (param_1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_004282e0(param_1,0);
    FUN_00428400(local_14,local_30);
    uVar2 = FID_conflict_begin(local_20);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 == '\0') {
      local_1c = FUN_00421ea0();
      local_1c = local_1c + 0xc;
      local_10 = 0;
      FUN_00424640(local_8);
      local_18 = 0;
      while( true ) {
        uVar2 = FID_conflict_begin(local_24);
        cVar1 = FUN_00420f10(uVar2);
        if (cVar1 == '\0') break;
        if (local_10 == 0) {
LAB_00430a80:
          uVar2 = FUN_00421ea0();
          FUN_00432510(uVar2);
          piVar4 = (int *)FUN_00421ea0();
          local_10 = *piVar4;
        }
        else {
          puVar3 = (undefined4 *)FUN_00421ea0();
          cVar1 = FUN_004282a0(local_10,*puVar3);
          if (cVar1 != '\0') goto LAB_00430a80;
        }
        FUN_00422190();
        local_18 = local_18 + 1;
      }
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

