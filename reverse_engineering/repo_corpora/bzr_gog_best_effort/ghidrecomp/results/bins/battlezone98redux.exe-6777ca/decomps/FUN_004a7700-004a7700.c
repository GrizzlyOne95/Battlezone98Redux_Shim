
void __thiscall FUN_004a7700(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  
  *(uint *)(param_1 + 0x210) = param_2 ^ 0x33333333;
  iVar1 = FUN_0046d060();
  if (0 < iVar1) {
    iVar1 = FUN_00417c80();
    iVar2 = FUN_0046d060();
    *(float *)(param_1 + 0x20c) = (float)iVar1 / (float)iVar2;
  }
  return;
}

