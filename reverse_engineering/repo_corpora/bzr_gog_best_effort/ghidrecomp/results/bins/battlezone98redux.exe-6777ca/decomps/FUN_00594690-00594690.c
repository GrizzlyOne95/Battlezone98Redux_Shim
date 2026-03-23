
void __thiscall FUN_00594690(int param_1,float param_2,float param_3,int *param_4,int *param_5)

{
  *param_4 = (int)((param_2 - *(float *)(param_1 + 0x30)) * *(float *)(param_1 + 0x40)) +
             *(int *)(param_1 + 0x44);
  *param_5 = *(int *)(param_1 + 0x48) -
             (int)((param_3 - *(float *)(param_1 + 0x34)) * *(float *)(param_1 + 0x40));
  return;
}

