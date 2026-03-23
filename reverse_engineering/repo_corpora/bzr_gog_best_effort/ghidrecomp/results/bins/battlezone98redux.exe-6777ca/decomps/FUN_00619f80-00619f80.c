
ushort FUN_00619f80(void)

{
  ushort uVar1;
  
  uVar1 = GetKeyState(0x12);
  return uVar1 & 0x1000;
}

