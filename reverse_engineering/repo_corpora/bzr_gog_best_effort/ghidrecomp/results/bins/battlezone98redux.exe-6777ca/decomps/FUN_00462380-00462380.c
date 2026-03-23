
uint __fastcall FUN_00462380(int param_1)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x15c) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(int *)(param_1 + 0x160) << 0x14 | *(uint *)(param_1 + 0x15c) & 0xfffff;
  }
  return uVar1;
}

