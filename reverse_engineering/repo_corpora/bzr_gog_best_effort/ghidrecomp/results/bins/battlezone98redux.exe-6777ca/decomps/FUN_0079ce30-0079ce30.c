
undefined4 FUN_0079ce30(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  _Vector_alloc<>(param_3);
  puVar1 = (undefined4 *)FID_conflict_begin(local_10);
  local_c = *puVar1;
  uVar2 = FUN_00416410();
  uVar3 = get(uVar2);
  FUN_0079ce90(local_14,local_c,uVar3,uVar2);
  return local_8;
}

