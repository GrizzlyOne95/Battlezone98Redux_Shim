
byte FUN_007faa20(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar4 = param_2;
  uVar5 = param_3;
  uVar3 = FUN_007f7af0(param_1,param_2,param_3);
  bVar1 = FUN_007faab0(uVar3,uVar4,uVar5);
  uVar4 = FUN_007fabf0(param_1,param_2,param_3);
  bVar2 = FUN_007fab20(uVar4,param_2,param_3);
  return bVar2 & bVar1;
}

