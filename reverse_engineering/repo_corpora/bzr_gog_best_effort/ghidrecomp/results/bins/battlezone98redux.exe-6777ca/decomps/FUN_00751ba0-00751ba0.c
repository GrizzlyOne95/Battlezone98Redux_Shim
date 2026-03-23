
undefined4
FUN_00751ba0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int *local_8;
  
  FUN_0073a970(&local_18);
  local_20 = local_18;
  local_1c = local_14;
  local_8 = (int *)FUN_007508c0();
  uVar3 = 0;
  puVar2 = &local_20;
  puVar1 = (undefined4 *)FUN_0073a970(local_28);
  uVar3 = (**(code **)(*local_8 + 0x6c))(*puVar1,puVar1[1],param_3,puVar2,param_4,param_5,uVar3);
  return uVar3;
}

