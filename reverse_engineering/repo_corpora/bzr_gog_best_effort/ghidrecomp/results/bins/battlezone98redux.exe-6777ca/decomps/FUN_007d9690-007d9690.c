
undefined4 FUN_007d9690(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c;
  
  puVar1 = (undefined4 *)FID_conflict_begin(local_14);
  local_10 = *puVar1;
  local_c = FID_conflict__Pdif(param_2,local_10);
  FID_conflict_insert(local_c,1,param_3);
  uVar2 = param_1;
  uVar3 = local_c;
  FID_conflict_begin(local_18);
  FID_conflict_operator_(uVar2,uVar3);
  return param_1;
}

