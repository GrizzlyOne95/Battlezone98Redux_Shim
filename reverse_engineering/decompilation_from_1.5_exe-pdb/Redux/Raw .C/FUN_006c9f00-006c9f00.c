
void __fastcall FUN_006c9f00(int param_1)

{
  int iVar1;
  
  while (*(int *)(param_1 + 8) != 0) {
    iVar1 = *(int *)(param_1 + 8);
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 8) + 0xc);
    FUN_006d8a70(iVar1);
    *(undefined4 *)(iVar1 + 0xc) = 0;
    *(undefined4 *)(iVar1 + 0x10) = 0;
  }
  FUN_006cec20();
  return;
}

