
uint FUN_005c9580(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_004da060(param_1);
  uVar2 = FUN_004da060(param_2);
  if ((iVar1 == 0) || (uVar2 == 0)) {
    uVar2 = uVar2 & 0xffffff00;
  }
  else {
    uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))();
    uVar2 = FUN_004db560(uVar3);
  }
  return uVar2;
}

