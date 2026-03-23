
void __thiscall FUN_005cdf70(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00462630(param_2,param_1);
  if (iVar1 != 0) {
    uVar2 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))(0x10000001);
    FUN_0062de80(uVar2);
  }
  return;
}

