
void __thiscall FUN_004a7230(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00451de0();
  if (iVar1 != 0) {
    param_2 = 1;
  }
  FUN_004a7300(param_1 + 0x111c,param_2,param_3);
  if (param_3 == 0) {
    *(undefined4 *)(param_1 + 0x1124) = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(param_3 + 0x18) + 0xc))();
    *(undefined4 *)(param_1 + 0x1124) = uVar2;
  }
  return;
}

