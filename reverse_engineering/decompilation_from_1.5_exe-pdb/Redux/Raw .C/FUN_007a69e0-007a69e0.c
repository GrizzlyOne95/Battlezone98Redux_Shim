
void __fastcall FUN_007a69e0(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_007cb1a0();
  if (iVar1 == 0) {
    FUN_0056f7e0();
  }
  else {
    *(undefined4 *)(param_1 + 0x198) = *(undefined4 *)(iVar1 + 0x30);
    *(undefined4 *)(param_1 + 0x19c) = *(undefined4 *)(iVar1 + 0x34);
    *(undefined4 *)(param_1 + 0x1a0) = *(undefined4 *)(iVar1 + 0x38);
    *(undefined4 *)(param_1 + 0x1a4) = *(undefined4 *)(iVar1 + 0x3c);
  }
  return;
}

