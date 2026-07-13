
bool FUN_005c96a0(undefined4 param_1,undefined4 param_2,float param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  float10 extraout_ST0;
  
  iVar2 = FUN_00462630(param_1);
  iVar3 = FUN_00462630(param_2);
  if ((iVar2 == 0) || (iVar3 == 0)) {
    bVar1 = false;
  }
  else {
    uVar4 = (**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
    uVar4 = (**(code **)(*(int *)(iVar2 + 0x18) + 0xc))(uVar4);
    FUN_00462010(uVar4);
    bVar1 = (float)extraout_ST0 < param_3 * param_3;
  }
  return bVar1;
}

