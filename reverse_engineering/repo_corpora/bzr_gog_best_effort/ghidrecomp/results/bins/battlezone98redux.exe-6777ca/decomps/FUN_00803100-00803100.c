
undefined4 FUN_00803100(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_1c [12];
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  uVar1 = FUN_007e1640(param_2,param_3,param_4);
  allocator<>(uVar1);
  puVar3 = local_c;
  uVar1 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_008036c0(local_10,uVar2,puVar3,uVar1);
  puVar3 = local_10;
  uVar1 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_008036f0(local_1c,uVar1,puVar3,param_4);
  FUN_007fe640(local_1c);
  return param_1;
}

