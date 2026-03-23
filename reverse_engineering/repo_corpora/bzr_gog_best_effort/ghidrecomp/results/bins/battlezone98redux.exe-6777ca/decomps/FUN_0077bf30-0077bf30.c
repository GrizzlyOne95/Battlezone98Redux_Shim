
void __fastcall FUN_0077bf30(int param_1)

{
  undefined4 local_10;
  undefined4 local_c;
  
  if (*(char *)(param_1 + 0x14) != '\0') {
    if (*(int *)(param_1 + 0x44) == 0) {
      if (*(char *)(param_1 + 0x85) != '\0') {
        FUN_0077b000();
      }
    }
    else {
      for (local_c = 0; local_c < (int)*(float *)(param_1 + 0x48); local_c = local_c + 1) {
        for (local_10 = 0; local_10 < (int)*(float *)(param_1 + 0x4c); local_10 = local_10 + 1) {
          FUN_00778450((int)*(float *)(param_1 + 0x4c) * local_c + local_10);
        }
      }
    }
  }
  return;
}

