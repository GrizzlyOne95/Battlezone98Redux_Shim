
void __fastcall FUN_00613d10(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x34) + 0x230);
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  uVar2 = FUN_004f1500(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x10));
  *(undefined4 *)(param_1 + 0x38) = uVar2;
  return;
}

