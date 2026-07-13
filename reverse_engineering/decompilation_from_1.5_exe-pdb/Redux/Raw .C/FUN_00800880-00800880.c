
undefined4 FUN_00800880(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_44 [28];
  undefined1 local_28 [16];
  undefined1 local_18 [20];
  
  uVar1 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007fe890(uVar1);
  puVar3 = local_18;
  uVar1 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_00800900(local_28,uVar2,puVar3,uVar1);
  puVar3 = local_28;
  uVar1 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_00800930(local_44,uVar1,puVar3,param_4);
  FUN_007fe3a0(local_44);
  return param_1;
}

