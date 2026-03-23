
void __thiscall FUN_004a72a0(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  FUN_004a7300(param_1 + 0x112c,param_2,param_3);
  if (param_3 == 0) {
    *(undefined4 *)(param_1 + 0x1134) = 0;
  }
  else {
    uVar1 = (**(code **)(*(int *)(param_3 + 0x18) + 0xc))();
    *(undefined4 *)(param_1 + 0x1134) = uVar1;
  }
  return;
}

