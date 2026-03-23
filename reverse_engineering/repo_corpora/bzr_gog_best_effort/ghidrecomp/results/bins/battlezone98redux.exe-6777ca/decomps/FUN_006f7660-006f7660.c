
void __fastcall FUN_006f7660(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined1 local_5;
  
  uVar1 = *(int *)(param_1 + 0xc) + -1 + *(int *)(param_1 + 0x10);
  iVar2 = FUN_004bb930(uVar1);
  iVar2 = *(int *)(*(int *)(param_1 + 4) + iVar2 * 4) + (uVar1 % 2) * 8;
  Getal(&local_5);
  destroy<>(iVar2);
  iVar2 = *(int *)(param_1 + 0x10) + -1;
  *(int *)(param_1 + 0x10) = iVar2;
  if (iVar2 == 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return;
}

