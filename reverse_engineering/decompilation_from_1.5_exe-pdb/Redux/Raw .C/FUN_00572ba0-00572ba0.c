
void __thiscall FUN_00572ba0(undefined4 param_1,ushort param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)param_2;
  FUN_00764760(uVar1,param_1);
  iVar2 = FUN_00746720(uVar1);
  if (iVar2 != 0) {
    *(undefined1 *)(iVar2 + 0x44) = 1;
  }
  return;
}

