
undefined4 FUN_007ffc00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_24 [24];
  undefined1 local_c [7];
  undefined1 local_5;
  
  FUN_007e0b60(&local_5,param_2,param_3,param_4);
  puVar3 = &local_5;
  uVar2 = param_4;
  uVar1 = FUN_007e31c0(param_2,puVar3,param_4);
  FUN_007ffe70(local_c,uVar1,puVar3,uVar2);
  puVar3 = local_c;
  uVar2 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_007ffea0(local_24,uVar2,puVar3,param_4);
  FUN_007fe340(local_24);
  return param_1;
}

