
void FUN_006a90a0(int param_1,int param_2)

{
  *(int *)(&DAT_02ce9aa4 + param_1 * 0x1e0) = *(int *)(&DAT_02ce9aa4 + param_1 * 0x1e0) + param_2;
  if (*(int *)(&DAT_02ce9aa4 + param_1 * 0x1e0) < 0) {
    *(undefined4 *)(&DAT_02ce9aa4 + param_1 * 0x1e0) = 0;
  }
  return;
}

