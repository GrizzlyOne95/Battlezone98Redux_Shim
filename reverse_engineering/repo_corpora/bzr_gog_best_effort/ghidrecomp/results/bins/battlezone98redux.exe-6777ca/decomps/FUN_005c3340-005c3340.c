
void __thiscall FUN_005c3340(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  FUN_00461890(param_2,param_3);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  *(undefined4 *)(param_1 + 0x3c) = 0xbf800000;
  *(undefined1 *)(param_1 + 0x48) = 1;
  uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 4))();
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  FUN_005c3fd0();
  return;
}

