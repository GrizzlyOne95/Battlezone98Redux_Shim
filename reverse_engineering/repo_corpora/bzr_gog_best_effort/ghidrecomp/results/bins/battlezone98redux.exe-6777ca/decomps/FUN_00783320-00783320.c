
void FUN_00783320(int param_1,float param_2,float param_3)

{
  uint uVar1;
  ushort *puVar2;
  uint uVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = 0;
  uVar3 = (int)(param_2 * DAT_02cc50e4) & 0xfffffffc;
  uVar1 = (int)(param_3 * DAT_02cc50e4) & 0xfffffffc;
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      *(float *)(param_1 + local_10 * 0xc) = (float)(int)(uVar3 + local_c) * DAT_02cc50e0;
      *(float *)(param_1 + 8 + local_10 * 0xc) = (float)(int)(uVar1 + local_8) * DAT_02cc50e0;
      puVar2 = (ushort *)FUN_00492d60(uVar3 + local_c,uVar1 + local_8);
      *(float *)(param_1 + 4 + local_10 * 0xc) = (float)(*puVar2 & 0xfff) * 0.1;
      local_10 = local_10 + 1;
    }
  }
  return;
}

