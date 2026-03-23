
undefined4 * FUN_0058a380(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [8];
  undefined4 local_1c [2];
  undefined4 *local_14;
  undefined4 local_10;
  undefined4 local_c [2];
  
  local_10 = FUN_0044eea0(param_2);
  FUN_0044eff0(local_c,local_10);
  uVar2 = FUN_0058a4b0(local_24,local_10);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 == '\0') {
    FUN_0044ef90(param_1);
  }
  else {
    uVar2 = param_2;
    uVar3 = FUN_00422e80(param_2);
    uVar3 = FUN_00417780(uVar3);
    cVar1 = FUN_0044ef20(uVar3,uVar2);
    if (cVar1 != '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
    uVar2 = FUN_00422e80();
    uVar2 = FUN_00417780(uVar2);
    cVar1 = FUN_0044ef20(param_2,uVar2);
    if (cVar1 == '\0') {
      FUN_0044ec90(local_2c,local_c[0]);
      local_14 = local_1c;
    }
    else {
      local_14 = (undefined4 *)FUN_0044ef90(local_28);
    }
    *param_1 = *local_14;
  }
  return param_1;
}

