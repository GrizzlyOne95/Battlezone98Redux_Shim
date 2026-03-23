
void __fastcall FUN_00511fc0(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    if ((*(uint *)(param_1 + 0x30) & *(uint *)(param_1 + 0x34) & 1 << ((byte)local_8 & 0x1f)) != 0)
    {
      (**(code **)(**(int **)(param_1 + 0x18 + local_8 * 4) + 8))();
    }
  }
  return;
}

