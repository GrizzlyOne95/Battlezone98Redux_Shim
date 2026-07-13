
undefined4 FUN_007ee5d0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_34 [28];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c [2];
  
  local_c[0] = FUN_004170c0();
  puVar1 = (undefined4 *)_Min_value<>(local_c,&stack0x00000008);
  uVar2 = *puVar1;
  puVar1 = &local_10;
  FID_conflict_begin(local_14);
  iterator__operator_(puVar1,uVar2);
  FUN_007ee650(param_1);
  puVar1 = (undefined4 *)FID_conflict_begin(local_18);
  FUN_007ef280(local_34,*puVar1,local_10);
  return 1;
}

