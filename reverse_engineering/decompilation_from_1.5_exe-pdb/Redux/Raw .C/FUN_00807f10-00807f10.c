
undefined4 FUN_00807f10(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 extraout_var;
  undefined1 local_10 [4];
  undefined1 local_c [7];
  undefined1 local_5;
  
  FUN_007e0b60(&local_5,param_2,param_3,param_4);
  puVar3 = &local_5;
  uVar2 = param_4;
  uVar1 = FUN_007e31c0(param_2,puVar3,param_4,extraout_var);
  FUN_007ffe70(local_c,uVar1,puVar3,uVar2);
  puVar3 = local_c;
  uVar2 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_00807f90(local_10,uVar2,puVar3,param_4);
  FUN_007fea40(local_10);
  return param_1;
}

