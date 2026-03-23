
float10 __thiscall FUN_005c9730(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  iVar1 = FUN_00462630(param_2,param_1);
  if (iVar1 == 0) {
    fVar3 = (float10)1e+30;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))(param_3);
    fVar3 = (float10)FUN_00462010(uVar2);
    fVar3 = (float10)FUN_00417910((float)fVar3);
  }
  return fVar3;
}

