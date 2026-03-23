
undefined4 FUN_007e9e10(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_9c [84];
  undefined1 local_48 [67];
  undefined1 local_5;
  
  FUN_007e0b60(&local_5,param_2,param_3,param_4);
  puVar3 = &local_5;
  uVar2 = param_4;
  uVar1 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_007e9f20(local_48,uVar1,puVar3,uVar2);
  puVar3 = local_48;
  uVar2 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_007e9f50(local_9c,uVar2,puVar3,param_4);
  FUN_007de3e0(local_9c);
  return param_1;
}

