
void __thiscall FUN_004d9880(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int local_8;
  
  param_2 = param_2 & *(uint *)(param_1 + 0x2c);
  uVar1 = *(uint *)(param_1 + 0x30);
  uVar2 = *(uint *)(param_1 + 0x30);
  *(uint *)(param_1 + 0x30) = param_2;
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    if (*(int *)(param_1 + 0x18 + local_8 * 4) != 0) {
      if ((1 << ((byte)local_8 & 0x1f) & ~uVar1 & param_2) == 0) {
        if ((1 << ((byte)local_8 & 0x1f) & ~param_2 & uVar2) != 0) {
          (**(code **)(**(int **)(param_1 + 0x18 + local_8 * 4) + 0x20))();
        }
      }
      else {
        (**(code **)(**(int **)(param_1 + 0x18 + local_8 * 4) + 0x1c))();
      }
    }
  }
  return;
}

