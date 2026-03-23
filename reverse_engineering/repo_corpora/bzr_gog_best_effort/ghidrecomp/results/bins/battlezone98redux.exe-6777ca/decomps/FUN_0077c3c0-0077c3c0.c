
void __thiscall
FUN_0077c3c0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  undefined4 local_20;
  undefined4 local_10;
  undefined4 local_c;
  
  for (local_10 = param_6; local_10 < param_7; local_10 = local_10 + 1) {
    for (local_c = param_4; local_c < param_5; local_c = local_c + 1) {
      **(float **)(param_1 + 0x6c) = (float)local_c * 5.0 + ((float)param_2 * 20.0 - 160.0);
      *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 4;
      **(undefined4 **)(param_1 + 0x6c) = 0;
      *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 4;
      **(float **)(param_1 + 0x6c) = (160.0 - (float)param_3 * 20.0) - (float)local_10 * 5.0;
      *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 4;
      if ((local_c == 0) || (local_10 == 0)) {
        local_20 = 0xffffff;
      }
      else {
        local_20 = 0xffffffff;
      }
      **(undefined4 **)(param_1 + 0x6c) = local_20;
      *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 4;
    }
  }
  return;
}

