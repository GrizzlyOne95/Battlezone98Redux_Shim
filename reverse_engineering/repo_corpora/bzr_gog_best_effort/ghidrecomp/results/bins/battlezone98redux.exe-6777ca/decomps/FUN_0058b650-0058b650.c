
void __thiscall FUN_0058b650(int param_1,undefined4 *param_2,undefined4 *param_3)

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
  puVar1[9] = *(uint *)(param_1 + 0x3038) ^ 0x80000000;
  puVar1[10] = 0;
  uVar2 = *(int *)(param_1 + 0x2c) + 1;
  *(uint *)(param_1 + 0x2c) = uVar2;
  if (0xff < uVar2) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}

