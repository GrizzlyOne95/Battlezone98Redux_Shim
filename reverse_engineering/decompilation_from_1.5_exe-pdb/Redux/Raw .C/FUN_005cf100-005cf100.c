
void __fastcall FUN_005cf100(int param_1)

{
  undefined4 uVar1;
  
  floor((*(double *)(*(int *)(param_1 + 0x14) + 0x48) -
        (double)*(float *)(*(int *)(param_1 + 0xc) + 0x78)) * (double)DAT_02cc50e4);
  uVar1 = FUN_0083f040();
  *(undefined4 *)(param_1 + 0xe4) = uVar1;
  floor((*(double *)(*(int *)(param_1 + 0x14) + 0x58) -
        (double)*(float *)(*(int *)(param_1 + 0xc) + 0x78)) * (double)DAT_02cc50e4);
  uVar1 = FUN_0083f040();
  *(undefined4 *)(param_1 + 0xe8) = uVar1;
  ceil(((double)*(float *)(*(int *)(param_1 + 0xc) + 0x78) +
       *(double *)(*(int *)(param_1 + 0x14) + 0x48)) * (double)DAT_02cc50e4);
  uVar1 = FUN_0083f040();
  *(undefined4 *)(param_1 + 0xec) = uVar1;
  ceil(((double)*(float *)(*(int *)(param_1 + 0xc) + 0x78) +
       *(double *)(*(int *)(param_1 + 0x14) + 0x58)) * (double)DAT_02cc50e4);
  uVar1 = FUN_0083f040();
  *(undefined4 *)(param_1 + 0xf0) = uVar1;
  return;
}

