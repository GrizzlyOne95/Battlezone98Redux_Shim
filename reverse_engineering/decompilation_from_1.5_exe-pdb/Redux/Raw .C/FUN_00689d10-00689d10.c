
void FUN_00689d10(undefined4 *param_1,undefined4 *param_2,int param_3,int param_4,char *param_5)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  int local_c;
  short local_8 [2];
  
  iVar2 = param_3;
  local_c = 0;
  bVar1 = false;
  fVar4 = (float10)FUN_00689a90(param_1);
  param_4 = (int)((float)param_4 + (float)fVar4);
  if (param_2 == &DAT_02cecee0) {
    FUN_00417990(*param_1);
    for (; *param_5 != '\0'; param_5 = param_5 + 1) {
      if (*param_5 == '\t') {
        for (; (!bVar1 && (*(int *)(&DAT_008ed6b0 + local_c * 4) <= param_3 - iVar2));
            local_c = local_c + 1) {
          if (*(int *)(&DAT_008ed6b0 + local_c * 4) == -1) {
            bVar1 = true;
          }
        }
        if (bVar1) {
          param_3 = param_3 + 0x20;
        }
        else {
          param_3 = iVar2 + *(int *)(&DAT_008ed6b0 + local_c * 4);
        }
      }
      else if (*param_5 == '\n') {
        local_c = 0;
        fVar4 = (float10)FUN_00689a70(param_1);
        param_4 = (int)((float)param_4 + (float)fVar4 + DAT_02bf0420 * 2.0);
        param_3 = iVar2;
      }
      else {
        local_8[0] = (short)*param_5;
        uVar3 = FUN_00689930(param_1,local_8,param_3,param_4,0x200005,0);
        FUN_0068c560(&DAT_02cecee0,uVar3);
        fVar4 = (float10)FUN_00689a20(param_1,*param_5);
        param_3 = (int)((float)param_3 + (float)fVar4);
      }
    }
  }
  return;
}

