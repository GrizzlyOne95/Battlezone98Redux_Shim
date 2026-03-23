
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00687550(int param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *local_34;
  int local_2c;
  int local_28;
  short *local_24;
  
  FUN_00684c80(1);
  FUN_00684c60(1);
  uVar6 = 2;
  uVar8 = DAT_00920ef4;
  uVar2 = FUN_00684bf0(2,DAT_00920ef4);
  FUN_00679d70(uVar2,uVar6,uVar8);
  FUN_0067a110(param_2,param_2 << 1);
  sVar1 = FUN_00684c10();
  uVar8 = DAT_02b79b2c;
  local_34 = (undefined4 *)FUN_0067a150(param_2);
  for (local_28 = 0; local_28 < param_2; local_28 = local_28 + 1) {
    uVar9 = 0;
    uVar7 = 0;
    uVar6 = 0xbf800000;
    uVar2 = param_3;
    fVar4 = (float10)FUN_004f90f0(uVar8,(float)*(int *)(param_1 + 4 + local_28 * 8) - _DAT_008ed0e0,
                                  0xbf800000,param_3,0,0);
    fVar5 = (float)fVar4;
    fVar4 = (float10)FUN_004f90a0(uVar8,(float)*(int *)(param_1 + local_28 * 8) - _DAT_008ed0e0,
                                  fVar5);
    puVar3 = (undefined4 *)FUN_00446360((float)fVar4,fVar5,uVar6,uVar2,uVar7,uVar9);
    *local_34 = *puVar3;
    local_34[1] = puVar3[1];
    local_34[2] = puVar3[2];
    local_34[3] = puVar3[3];
    local_34[4] = puVar3[4];
    local_34[5] = puVar3[5];
    local_34 = local_34 + 6;
  }
  local_24 = (short *)FUN_0067a1e0(param_2 << 1);
  for (local_2c = 0; local_2c < param_2 + -1; local_2c = local_2c + 1) {
    *local_24 = sVar1 + (short)local_2c;
    local_24[1] = sVar1 + 1 + (short)local_2c;
    local_24 = local_24 + 2;
  }
  *local_24 = (short)param_2 + -1 + sVar1;
  local_24[1] = sVar1;
  FUN_00679f10();
  FUN_0083e885();
  return;
}

