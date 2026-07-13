
bool FUN_005cd300(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  if (DAT_02a13c7b == '\0') {
    DAT_009182a4 = DAT_009182a4 + 1;
    uVar1 = FUN_00460fc0(param_1);
    iVar2 = FUN_00462630(param_4,uVar1);
    if (iVar2 != 0) {
      uVar3 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))();
      FUN_00821fd0(uVar1,&param_2,&param_3,uVar3);
    }
    iVar2 = FUN_00821fb0();
    bVar4 = iVar2 == 1;
  }
  else {
    bVar4 = true;
  }
  return bVar4;
}

