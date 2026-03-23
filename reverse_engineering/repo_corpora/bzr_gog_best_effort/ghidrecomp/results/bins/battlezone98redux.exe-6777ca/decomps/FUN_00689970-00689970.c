
void FUN_00689970(int param_1,int param_2)

{
  int local_8;
  
  if (8 < param_1) {
    param_1 = 8;
  }
  for (local_8 = 0; local_8 < param_1; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_008ed6b0 + local_8 * 4) = *(undefined4 *)(param_2 + local_8 * 4);
  }
  for (; local_8 < 8; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_008ed6b0 + local_8 * 4) = 0xffffffff;
  }
  return;
}

