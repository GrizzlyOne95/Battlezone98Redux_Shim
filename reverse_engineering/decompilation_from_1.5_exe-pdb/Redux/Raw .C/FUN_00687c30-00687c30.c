
void FUN_00687c30(int param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (199 < local_8) {
      return;
    }
    if (*(int *)(&DAT_02b7a4ac + local_8 * 0x97c) == param_1) break;
    local_8 = local_8 + 1;
  }
  *(undefined4 *)(&DAT_02b7a4ac + local_8 * 0x97c) = 0;
  (&DAT_02b7a4b0)[local_8 * 0x97c] = 0;
  return;
}

