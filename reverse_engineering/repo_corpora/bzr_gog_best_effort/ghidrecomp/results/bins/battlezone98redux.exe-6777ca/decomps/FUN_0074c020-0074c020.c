
undefined1 * FUN_0074c020(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  undefined1 local_c [4];
  undefined4 local_8;
  
  puVar2 = (undefined4 *)FUN_00578c20(local_14,param_1);
  local_8 = *puVar2;
  uVar3 = FID_conflict_begin(local_18);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    puVar4 = local_c;
    FUN_00421ea0(puVar4,param_2);
    FUN_00421e00(puVar4,param_2);
    puVar4 = local_1c;
    FUN_00421ea0(puVar4);
    uVar3 = FID_conflict_begin(puVar4);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 != '\0') {
      FUN_00421ea0();
      puVar4 = (undefined1 *)FUN_0041f870();
      return puVar4;
    }
  }
  return &DAT_008a1ad8;
}

