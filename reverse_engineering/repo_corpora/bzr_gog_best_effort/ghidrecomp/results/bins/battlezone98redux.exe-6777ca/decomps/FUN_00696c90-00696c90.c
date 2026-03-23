
void FUN_00696c90(int param_1,int param_2,int param_3,int param_4,byte param_5)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + (*(int *)(param_2 + 0x40) + param_4) * 4) +
                  (*(int *)(param_2 + 0x44) + param_3) * 4);
  if (*(int *)(iVar1 + 0x14) != 0) {
    *(undefined4 *)(iVar1 + 0x74) = 0;
    *(undefined1 *)(iVar1 + 0x78) = 0;
    FUN_006a5000(DAT_00920f04,*(undefined4 *)(iVar1 + 0x14));
  }
  *(byte *)(param_2 + 0x78) = *(byte *)(param_2 + 0x78) & ~param_5;
  return;
}

