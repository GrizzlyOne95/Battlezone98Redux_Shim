
void __fastcall FUN_0079e8c0(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_007cb1a0();
  if (iVar1 == 0) {
    FUN_0056f7e0();
  }
  else {
    *(undefined4 *)(param_1 + 0x1c8) = *(undefined4 *)(iVar1 + 8);
    *(undefined4 *)(param_1 + 0x1cc) = *(undefined4 *)(iVar1 + 0xc);
    *(undefined4 *)(param_1 + 0x1d0) = *(undefined4 *)(iVar1 + 0x10);
    *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(iVar1 + 0x14);
  }
  return;
}

