
undefined4 FUN_004e4b90(int param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  float10 extraout_ST0;
  
  FUN_00462590(param_2);
  iVar2 = FUN_005e0f70(param_2);
  if (iVar2 != 0) {
    if ((*(int *)(iVar2 + 0xac) == 0x10) ||
       ((*(int *)(iVar2 + 0xac) == 3 && (iVar3 = FUN_00462380(), *(int *)(iVar2 + 0xb0) == iVar3))))
    {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      iVar3 = FUN_00462450();
      iVar4 = FUN_00462450();
      if (iVar3 < iVar4) {
        uVar5 = (**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
        uVar5 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(uVar5);
        FUN_00462010(uVar5);
        if ((float)extraout_ST0 <= 225.0) {
          uVar5 = 1;
        }
        else {
          uVar5 = 0;
        }
      }
      else {
        uVar5 = 0;
      }
    }
    else {
      uVar5 = 0;
    }
    return uVar5;
  }
  return 0;
}

