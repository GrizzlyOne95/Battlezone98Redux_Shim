
void FUN_00469900(float param_1,float param_2,float param_3,int param_4,char param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  char local_34;
  char local_1c;
  int local_14;
  int local_10;
  int local_c;
  
  if (param_5 == '\0') {
    local_1c = -1;
  }
  else {
    local_1c = '\x01';
  }
  fVar5 = (float10)FUN_00461fd0((param_1 - param_3) * DAT_02cc50e4,0,
                                (DAT_02ce99a0 - DAT_02ce99c0) + -1);
  iVar1 = FUN_00453d10((int)fVar5 - DAT_02ce99c0);
  fVar5 = (float10)FUN_00461fd0((param_1 + param_3) * DAT_02cc50e4,0,
                                (DAT_02ce99a0 - DAT_02ce99c0) + -1);
  iVar2 = FUN_00453d10((int)fVar5 - DAT_02ce99c0);
  fVar5 = (float10)FUN_00461fd0((param_2 - param_3) * DAT_02cc50e4,0,
                                (DAT_02ce99c4 - DAT_02cd9984) + -1);
  local_14 = FUN_00453d10((int)fVar5 - DAT_02cd9984);
  fVar5 = (float10)FUN_00461fd0((param_2 + param_3) * DAT_02cc50e4,0,
                                (DAT_02ce99c4 - DAT_02cd9984) + -1);
  iVar3 = FUN_00453d10((int)fVar5 - DAT_02cd9984);
  fVar6 = param_1 * DAT_02cc50e4;
  fVar11 = (float)DAT_02ce99c0;
  fVar7 = param_2 * DAT_02cc50e4;
  fVar12 = (float)DAT_02cd9984;
  fVar8 = param_3 * DAT_02cc50e4;
  local_c = (DAT_02ce99a0 - DAT_02ce99c0) * local_14 + iVar1;
  iVar4 = DAT_02ce99a0 - DAT_02ce99c0;
  for (; local_10 = iVar1, local_14 <= iVar3; local_14 = local_14 + 1) {
    for (; local_10 <= iVar2; local_10 = local_10 + 1) {
      fVar9 = (float)local_10 - ((fVar6 - fVar11) - 0.5);
      fVar10 = (float)local_14 - ((fVar7 - fVar12) - 0.5);
      if (fVar9 * fVar9 + fVar10 * fVar10 < fVar8 * fVar8) {
        local_34 = *(char *)(*(int *)(&DAT_0260d118 + param_4 * 4) + local_c) + local_1c;
        *(char *)(*(int *)(&DAT_0260d118 + param_4 * 4) + local_c) = local_34;
        if (local_34 < '\x01') {
          *(ushort *)(DAT_0260d180 + local_c * 2) =
               *(ushort *)(DAT_0260d180 + local_c * 2) & ~(ushort)(1 << ((byte)param_4 & 0x1f));
        }
        else {
          *(ushort *)(DAT_0260d180 + local_c * 2) =
               *(ushort *)(DAT_0260d180 + local_c * 2) | (ushort)(1 << ((byte)param_4 & 0x1f));
        }
      }
      local_c = local_c + 1;
    }
    local_c = local_c + (iVar4 - ((iVar2 - iVar1) + 1));
  }
  FUN_0058d090(param_1 - param_3,param_2 - param_3,param_1 + param_3,param_2 + param_3);
  return;
}

