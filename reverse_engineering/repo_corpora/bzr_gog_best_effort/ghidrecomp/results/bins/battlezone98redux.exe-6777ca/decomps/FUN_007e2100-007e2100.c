
undefined4 FUN_007e2100(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_60 [40];
  undefined1 local_38 [24];
  undefined1 local_20 [28];
  
  uVar1 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007de830(uVar1);
  puVar3 = local_20;
  uVar1 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_007e23e0(local_38,uVar2,puVar3,uVar1);
  puVar3 = local_38;
  uVar1 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_007e2410(local_60,uVar1,puVar3,param_4);
  FUN_007ddca0(local_60);
  return param_1;
}

