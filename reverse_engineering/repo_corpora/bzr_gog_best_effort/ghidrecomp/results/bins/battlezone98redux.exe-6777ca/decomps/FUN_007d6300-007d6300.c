
void FUN_007d6300(char *param_1)

{
  if (DAT_00946710 == 0) {
    DAT_00946710 = (int)fopen(s_debug_log_008f16e8,"at");
  }
  if (DAT_00946710 != 0) {
    fputs(param_1,(FILE *)DAT_00946710);
    fflush((FILE *)DAT_00946710);
    fclose((FILE *)DAT_00946710);
    DAT_00946710 = 0;
  }
  return;
}

