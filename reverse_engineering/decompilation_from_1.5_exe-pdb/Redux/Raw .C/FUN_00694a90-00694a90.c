
int FUN_00694a90(int param_1,int *param_2)

{
  int iVar1;
  int local_10;
  
  iVar1 = **(int **)(param_1 + 8);
  if (-1 < iVar1) {
    FUN_006a4030();
  }
  local_10 = (int)((float)*(int *)(param_1 + 0xc) *
                  *(float *)(&DAT_02bff188 + iVar1 * 4 + *param_2 * 400));
  if (local_10 < 1) {
    local_10 = 1;
  }
  return local_10;
}

