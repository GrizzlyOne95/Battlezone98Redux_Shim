
undefined4 FUN_005c8720(undefined4 param_1,float param_2)

{
  int iVar1;
  undefined4 uVar2;
  float10 extraout_ST0;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    (**(code **)(*(int *)(iVar1 + 0x18) + 0x1c))();
    if ((float)extraout_ST0 < param_2) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

