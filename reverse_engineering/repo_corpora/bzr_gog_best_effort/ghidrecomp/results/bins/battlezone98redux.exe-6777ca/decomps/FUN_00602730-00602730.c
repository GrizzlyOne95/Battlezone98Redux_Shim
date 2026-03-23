
void __fastcall FUN_00602730(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  *(undefined4 *)(iVar1 + 0xc4) = 0x3e800000;
  *(undefined4 *)(iVar1 + 0xd0) = 0x3e800000;
  *(undefined4 *)(iVar1 + 0xcc) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  return;
}

