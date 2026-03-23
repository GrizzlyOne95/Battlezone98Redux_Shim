
void __fastcall FUN_004e2490(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 1) {
    *(undefined4 *)(param_1 + 8) = 5;
  }
  else if (iVar1 == 2) {
    FUN_00601070();
  }
  else if (iVar1 == 3) {
    FUN_006028d0();
  }
  return;
}

