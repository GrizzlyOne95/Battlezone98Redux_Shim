
void __thiscall
FUN_005d1e00(int param_1,undefined4 *param_2,float param_3,float param_4,float param_5)

{
  undefined4 *puVar1;
  
  if (*(uint *)(param_1 + 0x4b0) < 0x20) {
    puVar1 = (undefined4 *)(param_1 + 0x30 + *(int *)(param_1 + 0x4b0) * 0x24);
    *(int *)(param_1 + 0x4b0) = *(int *)(param_1 + 0x4b0) + 1;
    *puVar1 = *param_2;
    puVar1[1] = param_2[1];
    puVar1[2] = param_2[2];
    puVar1[3] = param_3;
    puVar1[4] = param_3 * 0.5;
    puVar1[5] = (param_4 - param_3) / param_5;
    puVar1[6] = (param_4 - param_3 * 0.5) / param_5;
    puVar1[7] = 16.0 / param_5;
    puVar1[8] = (float)*(int *)(param_1 + 0x28);
  }
  return;
}

