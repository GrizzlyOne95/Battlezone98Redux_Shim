
int FUN_00692c40(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = param_2;
  for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
    iVar1 = (int)(((float)param_2 * (float)*(int *)(param_1 + 0x13c + local_8 * 4)) /
                 *(float *)(param_1 + 0x1bc));
    *(int *)(param_1 + 0xbc + local_8 * 4) = *(int *)(param_1 + 0xbc + local_8 * 4) + iVar1;
    local_c = local_c - iVar1;
  }
  return local_c;
}

