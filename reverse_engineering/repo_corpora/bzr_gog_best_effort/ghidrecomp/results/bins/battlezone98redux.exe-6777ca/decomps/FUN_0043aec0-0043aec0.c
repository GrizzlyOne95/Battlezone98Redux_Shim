
bool FUN_0043aec0(int param_1)

{
  int iVar1;
  
  *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xfffffffb;
  iVar1 = FUN_00439ec0(param_1);
  if (iVar1 != 0) {
    FUN_0043d060(param_1);
  }
  return iVar1 != 0;
}

