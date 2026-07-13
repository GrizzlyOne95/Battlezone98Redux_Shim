
void __fastcall FUN_004a7800(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    if (*(int *)(param_1 + 0x18 + local_8 * 4) != 0) {
      (**(code **)(**(int **)(param_1 + 0x18 + local_8 * 4) + 0xc))();
    }
  }
  return;
}

