
void __fastcall FUN_004c2b00(int param_1)

{
  int local_14;
  int local_10;
  int local_8;
  
  local_8 = 0;
  do {
    if (8 < local_8) {
      return;
    }
    if (*(&PTR_DAT_008e80b8)[local_8 * 3] != '\0') {
      local_14 = *(int *)(&PTR_PTR_008e80bc)[local_8 * 3];
      for (local_10 = 0; local_10 < *(int *)((&PTR_PTR_008e80bc)[local_8 * 3] + 4);
          local_10 = local_10 + 1) {
        if (*(int *)(&DAT_008e80c0 + local_8 * 0xc) == *(int *)(local_14 + 0xc)) {
          *(undefined **)(param_1 + 0xc) = (&PTR_PTR_008e80bc)[local_8 * 3];
          *(int *)(param_1 + 0x10) = local_10;
          *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x10) * 0x24 + **(int **)(param_1 + 0xc);
          return;
        }
        local_14 = local_14 + 0x24;
      }
    }
    local_8 = local_8 + 1;
  } while( true );
}

