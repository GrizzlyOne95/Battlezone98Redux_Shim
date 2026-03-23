
bool __fastcall FUN_005dfaf0(int param_1)

{
  int iVar1;
  int local_c;
  
  if (*(int *)(param_1 + 0xcc) < 1) {
    local_c = *(int *)(*(int *)(param_1 + 0xc4) + 0x4c);
  }
  else {
    local_c = *(int *)(*(int *)(param_1 + 0xc) + 0x4c);
  }
  iVar1 = FUN_00417c80();
  return local_c <= iVar1;
}

