
void FUN_00523260(void)

{
  int iVar1;
  
  if (((DAT_00920f04 != 0) && (*(int *)(DAT_00920f04 + 8) != 0)) &&
     (iVar1 = *(int *)(*(int *)(DAT_00920f04 + 8) + 0x60), iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *(undefined4 *)(iVar1 + 0x34) = 100;
    *(undefined4 *)(iVar1 + 0x38) = 100;
    *(undefined4 *)(iVar1 + 0x28) = 0;
    *(undefined4 *)(iVar1 + 0x58) = 100;
    *(undefined4 *)(iVar1 + 0x5c) = 100;
    *(undefined4 *)(iVar1 + 0x14) = 0;
    *(undefined4 *)(iVar1 + 100) = 100;
    *(undefined4 *)(iVar1 + 0x60) = 100;
  }
  return;
}

