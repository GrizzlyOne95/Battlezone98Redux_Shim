
void FUN_0058c1b0(int param_1)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = *(int *)(param_1 + 0x18);
  if (*(int *)(param_1 + 0x18) != -2) {
    while (local_8 != -1) {
      iVar1 = *(int *)(DAT_0091813c + local_8 * 0x10);
      *(int *)(DAT_0091813c + local_8 * 0x10) = DAT_008e8e00;
      DAT_008e8e00 = local_8;
      local_8 = iVar1;
    }
    *(undefined4 *)(param_1 + 0x18) = 0xfffffffe;
  }
  return;
}

