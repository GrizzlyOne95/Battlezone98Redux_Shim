
void FUN_0061a0d0(int param_1,int param_2)

{
  undefined4 local_8;
  
  if (DAT_008eacb8 == param_1) {
    DAT_008eacb8 = param_2;
  }
  for (local_8 = DAT_008ead14; local_8 < 8; local_8 = local_8 + 1) {
    if (*(int *)(local_8 * 0x238 + 0x2cebec8) == param_1) {
      *(int *)(local_8 * 0x238 + 0x2cebec8) = param_2;
    }
  }
  return;
}

