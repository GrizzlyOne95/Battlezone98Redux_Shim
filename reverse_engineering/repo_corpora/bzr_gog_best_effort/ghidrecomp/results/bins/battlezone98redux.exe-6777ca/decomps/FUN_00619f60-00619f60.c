
ushort FUN_00619f60(void)

{
  ushort uVar1;
  
  uVar1 = GetKeyState(0x11);
  return uVar1 & 0x1000;
}

