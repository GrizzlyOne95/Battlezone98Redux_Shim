
void __fastcall FUN_00726470(int param_1)

{
  int iVar1;
  undefined1 local_5;
  
  iVar1 = FUN_00713d00(*(undefined4 *)(param_1 + 0xc));
  iVar1 = *(uint *)(param_1 + 0xc) % 0x10 + *(int *)(*(int *)(param_1 + 4) + iVar1 * 4);
  Getal(&local_5);
  destroy<>(iVar1);
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

