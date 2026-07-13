
undefined4 * FUN_00578c20(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined4 *local_14;
  undefined1 local_10 [11];
  undefined1 local_5;
  
  FUN_00579220(local_10,param_2);
  uVar2 = FID_conflict_begin(local_20);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    uVar2 = FUN_00422f10(uVar2);
    FUN_00422f60(&local_5);
    cVar1 = FUN_00579110(param_2,uVar2);
    if (cVar1 == '\0') {
      local_14 = &local_18;
      goto LAB_00578ca2;
    }
  }
  local_14 = (undefined4 *)FID_conflict_begin(local_24);
LAB_00578ca2:
  *param_1 = *local_14;
  return param_1;
}

