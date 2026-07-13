
void FUN_004690f0(float param_1,float param_2,float param_3,float param_4,code *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_0260d178 != 0) {
    if (param_3 < param_1) {
      FUN_0046b580(&param_1,&param_3);
    }
    if (param_4 < param_2) {
      FUN_0046b580(&param_2,&param_4);
    }
    fVar4 = (float10)FUN_00461fd0(param_1 * DAT_02cc50e4,0,(DAT_02ce99a0 - DAT_02ce99c0) + -1);
    iVar1 = FUN_00453d10((int)fVar4 - DAT_02ce99c0);
    fVar4 = (float10)FUN_00461fd0(param_3 * DAT_02cc50e4,0,(DAT_02ce99a0 - DAT_02ce99c0) + -1);
    iVar2 = FUN_00453d10((int)fVar4 - DAT_02ce99c0);
    fVar4 = (float10)FUN_00461fd0(param_2 * DAT_02cc50e4,0,(DAT_02ce99c4 - DAT_02cd9984) + -1);
    local_c = FUN_00453d10((int)fVar4 - DAT_02cd9984);
    fVar4 = (float10)FUN_00461fd0(param_4 * DAT_02cc50e4,0,(DAT_02ce99c4 - DAT_02cd9984) + -1);
    iVar3 = FUN_00453d10((int)fVar4 - DAT_02cd9984);
    local_14 = (DAT_02ce99a0 - DAT_02ce99c0) * local_c;
    for (; local_c <= iVar3; local_c = local_c + 1) {
      local_10 = local_14 + iVar1;
      for (local_8 = iVar1; local_8 <= iVar2; local_8 = local_8 + 1) {
        (*param_5)(local_10,local_8 + DAT_02ce99c0,local_c + DAT_02cd9984);
        local_10 = local_10 + 1;
      }
      local_14 = (DAT_02ce99a0 - DAT_02ce99c0) + local_14;
    }
    FUN_0058d090(param_1,param_2,param_3,param_4);
  }
  return;
}

