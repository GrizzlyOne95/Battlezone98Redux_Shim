
void __fastcall FUN_007ceb00(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_5;
  
  iVar1 = FUN_007485a0(*(undefined4 *)(param_1 + 0xc));
  uVar2 = *(undefined4 *)(*(int *)(param_1 + 4) + iVar1 * 4);
  Getal(&local_5);
  destroy<>(uVar2);
  iVar1 = *(int *)(param_1 + 0x10) + -1;
  *(int *)(param_1 + 0x10) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  else {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  }
  return;
}

