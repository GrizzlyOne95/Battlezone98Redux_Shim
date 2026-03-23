
void FUN_006a1af0(void)

{
  int iVar1;
  int local_10;
  int local_c;
  
  FUN_0069f030();
  for (local_c = 0; local_c < 0x10; local_c = local_c + 1) {
    iVar1 = local_c * 0x1e0;
    *(undefined4 *)(&DAT_02ce9b94 + iVar1) = 0;
    *(undefined4 *)(&DAT_02ce9b98 + iVar1) = 0;
    *(undefined4 *)(&DAT_02ce9b9c + iVar1) = 0;
    *(undefined4 *)(&DAT_02ce9ba0 + iVar1) = 0;
    *(undefined4 *)(&DAT_02ce9ba4 + iVar1) = 0;
    *(undefined4 *)(&DAT_02ce9ba8 + iVar1) = 0;
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      *(undefined4 *)(iVar1 + 0x2ce9bac + local_10 * 4) = 0;
    }
  }
  return;
}

