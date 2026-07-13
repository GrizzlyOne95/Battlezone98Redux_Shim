
float10 FUN_005c9780(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  
  iVar1 = FUN_00462630(param_1);
  iVar2 = FUN_00462630(param_2);
  if ((iVar1 == 0) || (iVar2 == 0)) {
    fVar4 = (float10)1e+30;
  }
  else {
    uVar3 = (**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
    uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))(uVar3);
    fVar4 = (float10)FUN_00462010(uVar3);
    fVar4 = (float10)FUN_00417910((float)fVar4);
  }
  return fVar4;
}

