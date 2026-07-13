
bool FUN_007fab20(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  uint *puVar2;
  undefined4 uVar3;
  uint *puVar4;
  undefined4 uVar5;
  
  uVar3 = param_2;
  uVar5 = param_3;
  uVar1 = FUN_007f7af0(param_1,param_2,param_3);
  puVar2 = (uint *)FUN_007f7e40(uVar1,uVar3,uVar5);
  uVar3 = FUN_007f91a0(param_1,param_2,param_3);
  puVar4 = (uint *)max_size(uVar3,param_2,param_3);
  return *puVar4 < *puVar2;
}

