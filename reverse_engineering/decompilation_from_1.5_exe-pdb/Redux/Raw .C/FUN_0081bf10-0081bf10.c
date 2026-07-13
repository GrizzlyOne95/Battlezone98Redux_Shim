
void __thiscall FUN_0081bf10(int param_1,int param_2)

{
  undefined4 local_8;
  
  for (local_8 = 0; -1 < local_8; local_8 = local_8 + -1) {
    *(int *)(param_1 + local_8 * 4) = param_2;
  }
  if (param_2 != 0) {
    FUN_0081bf60();
  }
  return;
}

