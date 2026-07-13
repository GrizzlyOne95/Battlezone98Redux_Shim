
undefined4 __fastcall FUN_007cb1a0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x14c) < 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_0066b170(*(undefined4 *)(param_1 + 0x14c));
    uVar2 = *(undefined4 *)(iVar1 + 0x18);
  }
  return uVar2;
}

