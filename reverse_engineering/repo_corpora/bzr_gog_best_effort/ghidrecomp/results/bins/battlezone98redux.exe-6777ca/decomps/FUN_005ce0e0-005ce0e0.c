
uint FUN_005ce0e0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    iVar2 = FUN_00460fc0(param_2);
    if (iVar2 == 0) {
      uVar3 = FUN_007d6a70("Path not found %s",param_2);
      uVar3 = uVar3 & 0xffffff00;
    }
    else {
      uVar4 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
      uVar3 = FUN_004611b0(uVar4);
    }
  }
  return uVar3;
}

