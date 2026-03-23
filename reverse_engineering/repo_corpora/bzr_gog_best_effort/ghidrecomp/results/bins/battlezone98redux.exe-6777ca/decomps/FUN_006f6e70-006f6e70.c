
void __fastcall FUN_006f6e70(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int local_10;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6 [2];
  
  uVar2 = Getal(local_6);
  FUN_00423c20(uVar2);
  while (cVar1 = FUN_0041f890(), cVar1 == '\0') {
    FUN_006f7660();
  }
  local_10 = *(int *)(param_1 + 8);
  while (local_10 != 0) {
    local_10 = local_10 + -1;
    if (*(int *)(*(int *)(param_1 + 4) + local_10 * 4) != 0) {
      uVar3 = 2;
      uVar2 = *(undefined4 *)(*(int *)(param_1 + 4) + local_10 * 4);
      Getal(&local_7);
      deallocate(uVar2,uVar3);
      iVar4 = *(int *)(param_1 + 4) + local_10 * 4;
      Getal(&local_8);
      destroy<>(iVar4);
    }
  }
  if (*(int *)(param_1 + 4) != 0) {
    deallocate(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
  }
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

