
undefined4 * FUN_0044ecb0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined4 *local_14;
  undefined4 local_10;
  undefined4 local_c [2];
  
  local_10 = FUN_0044eea0(param_2);
  FUN_0044eff0(local_c,local_10);
  while( true ) {
    uVar2 = FUN_0044f020(local_20,local_10);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') {
      FUN_0044eaa0(param_1);
      return param_1;
    }
    uVar2 = param_2;
    uVar3 = FUN_0042de50(param_2);
    uVar3 = FUN_00417780(uVar3);
    cVar1 = FUN_0044ef20(uVar3,uVar2);
    if (cVar1 == '\0') break;
    FUN_0042da80();
  }
  uVar2 = FUN_0042de50();
  uVar2 = FUN_00417780(uVar2);
  cVar1 = FUN_0044ef20(param_2,uVar2);
  if (cVar1 == '\0') {
    local_18 = local_c[0];
    local_14 = (undefined4 *)FUN_0044ec90(local_28,local_c[0]);
  }
  else {
    local_14 = (undefined4 *)FUN_0044eaa0(local_24);
  }
  *param_1 = *local_14;
  return param_1;
}

