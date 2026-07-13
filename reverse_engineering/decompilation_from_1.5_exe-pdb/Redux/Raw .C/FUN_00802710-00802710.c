
undefined4 FUN_00802710(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_28 [16];
  undefined1 local_18 [19];
  undefined1 local_5;
  
  FUN_007e0b60(&local_5,param_2,param_3,param_4);
  puVar3 = &local_5;
  uVar2 = param_4;
  uVar1 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_00802b80(local_18,uVar1,puVar3,uVar2);
  puVar3 = local_18;
  uVar2 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_00802bb0(local_28,uVar2,puVar3,param_4);
  FUN_007fe500(local_28);
  return param_1;
}

