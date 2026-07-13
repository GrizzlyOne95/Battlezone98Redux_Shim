
undefined4 * FUN_0066acd0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined4 *local_14;
  undefined1 local_10 [11];
  undefined1 local_5;
  
  FUN_0066bad0(local_10,param_2);
  uVar2 = FID_conflict_begin(local_20);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    uVar2 = FUN_00422f10(uVar2);
    FUN_00422f60(&local_5);
    cVar1 = FUN_0066bb50(param_2,uVar2);
    if (cVar1 == '\0') {
      local_14 = &local_18;
      goto LAB_0066ad52;
    }
  }
  local_14 = (undefined4 *)FID_conflict_begin(local_24);
LAB_0066ad52:
  *param_1 = *local_14;
  return param_1;
}

