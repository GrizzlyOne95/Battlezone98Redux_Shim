
void FUN_004415f0(int *param_1,int param_2)

{
  int *piVar1;
  undefined1 local_30 [12];
  int *local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = *(int **)(param_2 + 0x28);
  if (local_24 == (int *)0x0) {
    piVar1 = (int *)FUN_00440000(local_30,0,0,0);
    local_20 = *piVar1;
    local_1c = piVar1[1];
    local_18 = piVar1[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
  }
  else {
    local_20 = local_24[3];
    local_1c = local_24[7];
    local_18 = local_24[0xb];
    local_14 = local_24[*local_24 + 2];
    local_10 = local_24[local_24[1] + 6];
    local_c = local_24[local_24[2] + 10];
  }
  *param_1 = local_20;
  param_1[1] = local_1c;
  param_1[2] = local_18;
  param_1[3] = local_14;
  param_1[4] = local_10;
  param_1[5] = local_c;
  FUN_0083e885();
  return;
}

