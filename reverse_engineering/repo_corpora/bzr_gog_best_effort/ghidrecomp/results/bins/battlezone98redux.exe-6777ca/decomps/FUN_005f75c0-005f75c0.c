
uint __thiscall FUN_005f75c0(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((*(int *)(param_1 + 0x18) == 0) && (param_2 != 3)) {
    param_1 = param_1 & 0xffffff00;
  }
  else {
    iVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 4))();
    iVar2 = FUN_00461430();
    if (iVar1 == iVar2) {
      param_1 = FUN_005f7470();
    }
    else {
      param_1 = FUN_005f7500();
    }
  }
  return param_1;
}

