
void FUN_0073bb60(undefined4 *param_1,undefined2 *param_2)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  
  FUN_0073bab0(param_1);
  FUN_00574aa0(*param_2);
  puVar1 = (undefined2 *)FUN_00747ac0(param_1);
  *puVar1 = *param_2;
  puVar2 = (undefined4 *)FUN_00747b70(param_2);
  *puVar2 = *param_1;
  puVar2[1] = param_1[1];
  puVar2[2] = param_1[2];
  puVar2[3] = param_1[3];
  return;
}

