
undefined4 FUN_00460790(undefined4 param_1)

{
  char extraout_AL;
  char cVar1;
  undefined3 extraout_var;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined3 uVar5;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  int local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  undefined1 local_14 [4];
  int local_10;
  undefined1 local_c [7];
  char local_5;
  
  FUN_004ccd10(param_1,"[AiPaths]");
  local_5 = extraout_AL;
  uVar5 = extraout_var;
  if (extraout_AL == '\0') goto LAB_004608fb;
  local_10 = 0;
  uVar2 = FUN_0042d8c0(local_c);
  while (local_5 != '\0') {
    uVar3 = FID_conflict_begin(local_2c);
    cVar1 = FUN_00420f10(uVar3);
    uVar2 = 0;
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_0042de50();
    local_24 = *piVar4;
    if (*(char *)(local_24 + 0xc) == '\0') {
      local_10 = local_10 + 1;
    }
    uVar2 = FUN_00438c10(local_28,0);
  }
  if (local_5 == '\0') {
LAB_00460853:
    local_18 = 0;
  }
  else {
    uVar2 = FUN_004cd1b0(param_1,&local_10,4,"count");
    if ((uVar2 & 0xff) == 0) goto LAB_00460853;
    local_18 = 1;
  }
  uVar5 = (undefined3)(uVar2 >> 8);
  local_5 = (char)local_18;
  if ((char)local_18 != '\0') {
    FUN_0042d8c0(local_14);
    uVar5 = extraout_var_00;
    while (local_5 != '\0') {
      uVar3 = FID_conflict_begin(local_34);
      cVar1 = FUN_00420f10(uVar3);
      uVar5 = 0;
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_0042de50();
      local_1c = *piVar4;
      if (*(char *)(local_1c + 0xc) == '\0') {
        if (local_5 == '\0') {
LAB_004608ec:
          local_20 = 0;
        }
        else {
          cVar1 = FUN_00460c20(param_1);
          if (cVar1 == '\0') goto LAB_004608ec;
          local_20 = 1;
        }
        local_5 = (char)local_20;
      }
      FUN_00438c10(local_30,0);
      uVar5 = extraout_var_01;
    }
  }
LAB_004608fb:
  return CONCAT31(uVar5,local_5);
}

