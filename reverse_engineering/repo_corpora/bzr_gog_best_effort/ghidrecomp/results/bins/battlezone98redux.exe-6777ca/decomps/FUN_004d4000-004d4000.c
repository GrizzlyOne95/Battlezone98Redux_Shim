
void __fastcall FUN_004d4000(int param_1)

{
  int iVar1;
  
  FUN_00601730();
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  if (*(float *)(iVar1 + 0xd0) == 1.0) {
    *(undefined4 *)(iVar1 + 0xd4) = 1;
  }
  else {
    *(undefined4 *)(iVar1 + 0xd4) = 0;
  }
  return;
}

