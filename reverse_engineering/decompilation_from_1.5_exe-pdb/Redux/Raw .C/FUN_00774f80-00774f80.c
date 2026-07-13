
uint FUN_00774f80(int param_1,int param_2)

{
  double dVar1;
  undefined4 uVar2;
  ushort *puVar3;
  uint uVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  int local_14;
  
  local_14 = 0;
  while( true ) {
    if (0xf < local_14) {
      return 0xffffffff;
    }
    fVar5 = (float10)FUN_004588c0();
    fVar6 = ((float)fVar5 - (float)DAT_008f050c * 0.5) + (float)*(double *)(param_2 + 0x160);
    fVar5 = (float10)FUN_004588c0();
    fVar7 = (float)DAT_008f050c;
    dVar1 = *(double *)(param_2 + 0x170);
    FUN_00461fd0();
    uVar2 = FUN_0083f040();
    FUN_00461fd0(fVar6 * DAT_02cc50e4,uVar2);
    uVar2 = FUN_0083f040();
    puVar3 = (ushort *)FUN_004c0fe0(uVar2);
    uVar4 = (int)(uint)*puVar3 >> 0xc;
    if ((uVar4 == (*puVar3 >> 8 & 0xf)) && (0 < *(int *)(&DAT_02c00ef8 + uVar4 * 0x44))) break;
    local_14 = local_14 + 1;
  }
  *(float *)(param_1 + 0x10) = fVar6;
  *(float *)(param_1 + 0x18) = ((float)fVar5 - fVar7 * 0.5) + (float)dVar1;
  fVar5 = (float10)FUN_007855e0((double)*(float *)(param_1 + 0x10),
                                (double)*(float *)(param_1 + 0x18));
  *(float *)(param_1 + 0x14) = (float)fVar5;
  return uVar4;
}

