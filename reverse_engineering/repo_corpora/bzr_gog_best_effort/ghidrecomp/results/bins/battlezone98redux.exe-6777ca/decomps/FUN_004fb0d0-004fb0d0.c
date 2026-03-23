
void FUN_004fb0d0(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float local_20;
  float local_1c;
  uint local_18;
  int local_8;
  
  uVar1 = rand();
  uVar2 = rand();
  local_18 = 1;
  fVar5 = ((float)param_1[2] - (float)param_1[4]) / 32.0;
  param_1[0x10d] = param_1[1];
  param_1[0x10e] = param_1[2];
  param_1[0x10f] = param_1[3];
  param_1[0x40d] = 1;
  param_1[0x10c] = 0;
  if ((param_1[0x40e] == 0) && (0x3fff < (int)uVar1)) {
    *param_1 = 1;
    FUN_004fac70(param_1,0,0x20,0,(uVar2 & 3) + 1,(uVar1 & 3) + 2,fVar5);
  }
  else {
    iVar3 = rand();
    iVar4 = rand();
    for (local_8 = 1; local_8 < 0x20; local_8 = local_8 + 1) {
      if ((local_18 & uVar1 * 0x10000 + iVar3) == 0) {
        local_1c = -1.0;
      }
      else {
        local_1c = 1.0;
      }
      if ((local_18 & uVar2 * 0x10000 + iVar4) == 0) {
        local_20 = -1.0;
      }
      else {
        local_20 = 1.0;
      }
      param_1[local_8 * 3 + 0x10d] = (float)param_1[(local_8 + -1) * 3 + 0x10d] + local_1c;
      param_1[local_8 * 3 + 0x10e] = (float)param_1[(local_8 + -1) * 3 + 0x10e] - fVar5;
      param_1[local_8 * 3 + 0x10f] = (float)param_1[(local_8 + -1) * 3 + 0x10f] + local_20;
      *(char *)(param_1 + local_8 + 0xb) = (char)local_8 + -1;
      *(char *)((int)param_1 + local_8 * 4 + 0x2d) = (char)local_8;
      *(char *)((int)param_1 + local_8 * 4 + 0x2e) =
           (char)((int)(local_8 * -100 + (local_8 * -100 >> 0x1f & 0x1fU)) >> 5) + -0x6a;
      *(undefined1 *)((int)param_1 + local_8 * 4 + 0x2f) = DAT_009b7cb0;
      param_1[0x10c] = param_1[0x10c] + 1;
      param_1[0x40d] = param_1[0x40d] + 1;
      local_18 = local_18 << 1;
    }
    *param_1 = 0;
  }
  return;
}

