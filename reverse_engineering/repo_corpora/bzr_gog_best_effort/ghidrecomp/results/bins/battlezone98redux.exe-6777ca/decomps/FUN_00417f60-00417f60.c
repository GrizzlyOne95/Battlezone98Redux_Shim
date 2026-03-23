
undefined4 __thiscall FUN_00417f60(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((1 << ((byte)param_2 & 0x1f) & *(uint *)(param_1 + 0x2c)) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x18 + param_2 * 4);
  }
  return uVar1;
}

