
undefined4 * FUN_006d0f80(undefined4 *param_1,undefined4 param_2,undefined4 param_3,uint *param_4)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  uint local_8;
  
  local_8 = *param_4;
  uVar1 = FUN_0048a830();
  if (local_8 < uVar1) {
    puVar3 = local_10;
    uVar5 = param_2;
    uVar6 = param_3;
    FUN_006cf480(local_8);
    puVar2 = (undefined4 *)FUN_004fee40(puVar3);
    uVar4 = *puVar2;
    puVar3 = local_14;
    FUN_006cf480(local_8);
    puVar2 = (undefined4 *)FID_conflict_begin(puVar3);
    copy<>(local_1c,*puVar2,uVar4,uVar5,uVar6);
  }
  *param_1 = param_2;
  param_1[1] = param_3;
  return param_1;
}

