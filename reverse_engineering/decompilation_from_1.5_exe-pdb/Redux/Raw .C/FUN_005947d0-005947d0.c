
void __thiscall FUN_005947d0(int param_1,int param_2,int param_3,float *param_4,float *param_5)

{
  *param_4 = (float)(param_2 - *(int *)(param_1 + 0x44)) / *(float *)(param_1 + 0x40) +
             *(float *)(param_1 + 0x30);
  *param_5 = (float)(*(int *)(param_1 + 0x48) - param_3) / *(float *)(param_1 + 0x40) +
             *(float *)(param_1 + 0x34);
  return;
}

