
void __fastcall FUN_004e62f0(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 8) != 0xd) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
    *(undefined4 *)(iVar1 + 0xd4) = 0;
    *(undefined4 *)(iVar1 + 0xcc) = 0;
    if (*(int *)(param_1 + 8) == 2) {
      FUN_00601200();
    }
    else if (*(int *)(param_1 + 8) == 3) {
      FUN_00602920();
    }
  }
  return;
}

