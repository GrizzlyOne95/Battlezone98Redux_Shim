
void FUN_00689f10(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int local_24 [8];
  
  local_24[7] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24[0] = 0;
  local_24[1] = 0;
  local_24[2] = 0;
  local_24[3] = 0;
  local_24[4] = 0;
  local_24[5] = 0;
  local_24[6] = 0;
  if (param_2 * param_3 < 1) {
    piVar2 = local_24;
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_1 = *piVar2;
      piVar2 = piVar2 + 1;
      param_1 = param_1 + 1;
    }
  }
  else {
    local_24[0] = param_2;
    local_24[1] = param_3;
    local_24[4] = param_2 + -1;
    local_24[5] = param_3 + -1;
    local_24[6] = 1;
    piVar2 = local_24;
    for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_1 = *piVar2;
      piVar2 = piVar2 + 1;
      param_1 = param_1 + 1;
    }
  }
  FUN_0083e885();
  return;
}

