
bool __fastcall FUN_0049cdb0(int param_1)

{
  bool bVar1;
  
  bVar1 = *(int *)(param_1 + 0x3bc) != 0;
  if (bVar1) {
    *(undefined4 *)(param_1 + 0x3bc) = 0;
    *(undefined4 *)(param_1 + 0x304) = 0;
  }
  return bVar1;
}

