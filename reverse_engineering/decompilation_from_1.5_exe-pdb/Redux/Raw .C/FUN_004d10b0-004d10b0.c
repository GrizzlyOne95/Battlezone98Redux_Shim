
void __thiscall FUN_004d10b0(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = (undefined4 *)(param_1 + 0x30 + *(int *)(param_1 + 0x2c) * 0x30);
  *puVar1 = *param_2;
  puVar1[1] = param_2[1];
  puVar1[2] = param_2[2];
  puVar1[3] = param_2[3];
  puVar1[4] = param_2[4];
  puVar1[5] = param_2[5];
  puVar1[6] = *param_3;
  puVar1[7] = param_3[1];
  puVar1[8] = param_3[2];
  puVar1[9] = (float)*(int *)(param_1 + 0x630);
  puVar1[10] = 0;
  puVar1[0xb] = *(undefined4 *)(param_1 + 0x63c);
  uVar2 = *(int *)(param_1 + 0x2c) + 1;
  *(uint *)(param_1 + 0x2c) = uVar2;
  if (0x1f < uVar2) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}

