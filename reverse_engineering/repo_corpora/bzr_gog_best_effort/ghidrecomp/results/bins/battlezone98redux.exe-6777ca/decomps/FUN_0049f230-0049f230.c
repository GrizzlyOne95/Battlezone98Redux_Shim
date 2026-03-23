
undefined4 __thiscall FUN_0049f230(int param_1,byte param_2)

{
  uint uVar1;
  
  uVar1 = 1 << (param_2 & 0x1f) & *(uint *)(param_1 + 0x2c);
  return CONCAT31((int3)(uVar1 >> 8),uVar1 != 0);
}

