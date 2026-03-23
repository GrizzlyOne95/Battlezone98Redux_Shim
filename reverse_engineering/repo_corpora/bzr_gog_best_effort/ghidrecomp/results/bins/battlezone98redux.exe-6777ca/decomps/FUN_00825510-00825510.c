
undefined4 * FUN_00825510(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = malloc(0x3c);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = 4;
    puVar1[1] = 4;
    *puVar1 = 4;
    puVar1[3] = param_1[7];
    puVar1[4] = param_1[6];
    puVar1[5] = param_1[5];
    puVar1[6] = param_1[4];
    puVar1[7] = param_1[0xb];
    puVar1[8] = param_1[10];
    puVar1[9] = param_1[9];
    puVar1[10] = param_1[8];
    puVar1[0xb] = param_1[3];
    puVar1[0xc] = param_1[2];
    puVar1[0xd] = param_1[1];
    puVar1[0xe] = *param_1;
  }
  return puVar1;
}

