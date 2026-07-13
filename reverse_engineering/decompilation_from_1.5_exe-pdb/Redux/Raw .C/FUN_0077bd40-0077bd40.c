
void __thiscall FUN_0077bd40(int param_1,undefined4 param_2)

{
  undefined4 local_10;
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x44) != 0) {
    for (local_c = 0; local_c < (int)*(float *)(param_1 + 0x48); local_c = local_c + 1) {
      for (local_10 = 0; local_10 < (int)*(float *)(param_1 + 0x4c); local_10 = local_10 + 1) {
        FUN_007783d0(param_2);
      }
    }
  }
  return;
}

