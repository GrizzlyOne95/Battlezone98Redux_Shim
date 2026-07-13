
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fabb0(undefined4 param_1,int param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_2 + 0x1c) = 1;
  *(undefined4 *)(param_2 + 0x20) = 0;
  if (*(int *)(param_2 + 0x1038) == 0) {
    *(undefined4 *)(param_2 + 0x10) = 0;
  }
  else {
    iVar1 = FUN_0062c890(*(undefined4 *)(param_2 + 0x1038),param_1);
    *(float *)(param_2 + 0x10) = *(float *)(iVar1 + 0x14) * 0.75 + *(float *)(iVar1 + 0xc);
  }
  iVar1 = rand();
  *(float *)(param_2 + 0x28) =
       ((float)iVar1 * (DAT_009b7cb8 - _DAT_009b7cb4)) / 32767.0 + _DAT_009b7cb4;
  *(undefined4 *)(param_2 + 0x24) = DAT_009b7cbc;
  return;
}

