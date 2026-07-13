
undefined1 __thiscall FUN_005e1310(int param_1,int param_2)

{
  undefined1 uVar1;
  
  if ((param_2 < 1) || ((1 << ((byte)param_2 & 0x1f) & *(uint *)(param_1 + 0x17c)) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

