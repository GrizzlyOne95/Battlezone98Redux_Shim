
void FUN_00783430(int param_1,float param_2,float param_3)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = 0;
  iVar1 = (int)(param_2 * DAT_02cc50e4 + 0.5);
  iVar3 = (int)(param_3 * DAT_02cc50e4 + 0.5);
  for (local_8 = -1; local_8 < 2; local_8 = local_8 + 1) {
    for (local_c = -1; local_c < 2; local_c = local_c + 1) {
      *(float *)(param_1 + local_10 * 0xc) = (float)(iVar1 + local_c) * DAT_02cc50e0;
      *(float *)(param_1 + 8 + local_10 * 0xc) = (float)(iVar3 + local_8) * DAT_02cc50e0;
      puVar2 = (ushort *)FUN_00492d60(iVar1 + local_c,iVar3 + local_8);
      *(float *)(param_1 + 4 + local_10 * 0xc) = (float)(*puVar2 & 0xfff) * 0.1;
      local_10 = local_10 + 1;
    }
  }
  return;
}

