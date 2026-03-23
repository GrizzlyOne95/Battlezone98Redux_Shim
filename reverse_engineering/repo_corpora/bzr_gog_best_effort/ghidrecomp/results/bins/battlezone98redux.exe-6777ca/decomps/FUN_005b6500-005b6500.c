
void __thiscall FUN_005b6500(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  if ((param_2 != 0) && (iVar1 = FUN_00417c70(), iVar1 != 0)) {
    iVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 4))();
    iVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))();
    if (iVar2 == iVar3) {
      uVar4 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))(3);
      FUN_0043d1d0(param_2,uVar4);
    }
  }
  return;
}

