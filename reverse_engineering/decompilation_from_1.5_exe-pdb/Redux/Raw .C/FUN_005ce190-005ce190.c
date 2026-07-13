
undefined4 FUN_005ce190(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  float10 extraout_ST0;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    fVar3 = (float10)FUN_004624f0();
    FUN_0046fbd0();
    if ((float)fVar3 - (float)extraout_ST0 <= 0.0) {
      uVar2 = 0;
    }
    else {
      (**(code **)(*(int *)(iVar1 + 0x18) + 0x28))((float)fVar3 - (float)extraout_ST0);
      uVar2 = 1;
    }
  }
  return uVar2;
}

