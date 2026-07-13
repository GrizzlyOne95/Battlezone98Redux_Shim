
bool FUN_005c86c0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    bVar3 = false;
  }
  else {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    iVar1 = FUN_00462340(uVar2);
    bVar3 = iVar1 != 0;
  }
  return bVar3;
}

