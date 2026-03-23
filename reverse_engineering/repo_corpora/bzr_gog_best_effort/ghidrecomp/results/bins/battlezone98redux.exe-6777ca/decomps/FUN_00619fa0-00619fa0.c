
ushort FUN_00619fa0(void)

{
  ushort uVar1;
  
  uVar1 = GetKeyState(0x10);
  return uVar1 & 0x1000;
}

