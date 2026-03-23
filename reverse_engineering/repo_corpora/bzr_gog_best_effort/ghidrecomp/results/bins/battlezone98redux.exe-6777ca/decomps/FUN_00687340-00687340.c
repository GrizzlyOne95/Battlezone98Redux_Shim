
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00687340(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  short sVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  float10 fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 *local_30;
  int local_2c;
  int local_28;
  short *local_24;
  
  if ((DAT_02b79b34 != 0) && (cVar2 = FUN_0048efc0(), cVar2 != '\0')) {
    FUN_00684c80(1);
    FUN_00684c60(1);
    uVar8 = 2;
    uVar10 = DAT_00920ef4;
    uVar4 = FUN_00684bf0(2,DAT_00920ef4);
    FUN_00679d70(uVar4,uVar8,uVar10);
    iVar1 = param_2 * 2 + -2;
    FUN_0067a110(param_2,iVar1);
    sVar3 = FUN_00684c10();
    uVar10 = DAT_02b79b2c;
    local_30 = (undefined4 *)FUN_0067a150(param_2);
    for (local_28 = 0; local_28 < param_2; local_28 = local_28 + 1) {
      uVar11 = 0;
      uVar9 = 0;
      uVar8 = 0xbf800000;
      uVar4 = param_3;
      fVar6 = (float10)FUN_004f90f0(uVar10,(float)*(int *)(param_1 + 4 + local_28 * 8) -
                                           _DAT_008ed0e0,0xbf800000,param_3,0,0);
      fVar7 = (float)fVar6;
      fVar6 = (float10)FUN_004f90a0(uVar10,(float)*(int *)(param_1 + local_28 * 8) - _DAT_008ed0e0,
                                    fVar7);
      puVar5 = (undefined4 *)FUN_00446360((float)fVar6,fVar7,uVar8,uVar4,uVar9,uVar11);
      *local_30 = *puVar5;
      local_30[1] = puVar5[1];
      local_30[2] = puVar5[2];
      local_30[3] = puVar5[3];
      local_30[4] = puVar5[4];
      local_30[5] = puVar5[5];
      local_30 = local_30 + 6;
    }
    local_24 = (short *)FUN_0067a1e0(iVar1);
    for (local_2c = 0; local_2c < param_2 + -1; local_2c = local_2c + 1) {
      *local_24 = sVar3 + (short)local_2c;
      local_24[1] = sVar3 + 1 + (short)local_2c;
      local_24 = local_24 + 2;
    }
    FUN_00679f10();
  }
  FUN_0083e885();
  return;
}

