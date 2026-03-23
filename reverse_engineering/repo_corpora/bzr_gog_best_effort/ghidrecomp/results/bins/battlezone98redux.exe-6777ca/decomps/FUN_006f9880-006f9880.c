
undefined4 *
FUN_006f9880(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 extraout_var;
  undefined4 uVar6;
  
  puVar5 = param_4;
  uVar1 = FUN_0070af30(param_2 + 7);
  uVar6 = extraout_var;
  uVar2 = allocator<>(param_2 + 7);
  uVar3 = FUN_0070af90(param_2 + 7);
  uVar4 = FUN_0070af70(param_2 + 7);
  FUN_006af470(*param_2,param_2 + 1,uVar4,uVar3,uVar2,uVar1,puVar5,uVar6);
  uVar6 = param_4[1];
  *param_1 = *param_4;
  param_1[1] = uVar6;
  return param_1;
}

