
undefined4 FUN_007e2680(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_70 [40];
  undefined1 local_48 [32];
  undefined1 local_28 [36];
  
  uVar1 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007de380(uVar1);
  puVar3 = local_28;
  uVar1 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_007e2700(local_48,uVar2,puVar3,uVar1);
  puVar3 = local_48;
  uVar1 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_007e2730(local_70,uVar1,puVar3,param_4);
  FUN_007ddca0(local_70);
  return param_1;
}

