
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00616e80(int param_1)

{
  float10 fVar1;
  float fVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = -*(float *)(param_1 + 0x48);
  local_c = -*(float *)(param_1 + 0x60);
  fVar2 = local_c * local_c + local_8 * local_8;
  if (1e-05 <= fVar2) {
    fVar1 = (float10)FUN_00820570((double)fVar2);
    local_c = local_c * (float)fVar1;
    local_8 = local_8 * (float)fVar1;
  }
  else {
    local_8 = 0.0;
    local_c = -1.0;
  }
  DAT_02ceefa0 = local_c;
  DAT_02ceefa4 = 0;
  _DAT_02ceefa8 = -local_8;
  _DAT_02ceefac = 0;
  _DAT_02ceefb0 = 0x3f800000;
  _DAT_02ceefb4 = 0;
  _DAT_02ceefb8 = local_8;
  _DAT_02ceefbc = 0;
  _DAT_02ceefc0 = local_c;
  return;
}

