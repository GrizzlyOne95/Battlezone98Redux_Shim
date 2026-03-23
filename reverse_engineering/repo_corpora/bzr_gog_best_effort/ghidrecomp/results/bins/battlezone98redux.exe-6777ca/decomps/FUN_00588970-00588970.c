
void __thiscall FUN_00588970(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = (**(code **)(*(int *)(param_2 + 0x18) + 0x2c))();
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  *(int *)(param_1 + 0x3c) = param_2;
  puVar2 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  *(undefined4 *)(param_1 + 0x44) = *puVar2;
  *(undefined4 *)(param_1 + 0x48) = puVar2[1];
  *(undefined4 *)(param_1 + 0x4c) = puVar2[2];
  return;
}

