
uint __thiscall FUN_005ec9f0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x300) != 0) {
    uVar1 = FUN_0062e050(param_2);
    uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x300) + 0x18) + 0x30))();
    if (uVar1 == uVar2) {
      return uVar2 & 0xffffff00;
    }
  }
  uVar1 = FUN_004a88b0(param_2,param_3,param_4);
  return uVar1;
}

