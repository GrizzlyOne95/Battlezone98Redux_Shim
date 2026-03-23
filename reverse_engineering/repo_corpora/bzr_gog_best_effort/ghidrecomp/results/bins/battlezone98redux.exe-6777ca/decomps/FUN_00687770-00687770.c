
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00687770(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  short *psVar4;
  float10 fVar5;
  float fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  
  FUN_00684c80(1);
  FUN_00684c60(1);
  uVar9 = 2;
  uVar8 = DAT_00920ef4;
  uVar1 = FUN_00684bf0(2,DAT_00920ef4);
  FUN_00679d70(uVar1,uVar9,uVar8);
  FUN_0067a110(2,2);
  uVar9 = FUN_00684c10();
  uVar1 = DAT_02b79b2c;
  puVar2 = (undefined4 *)FUN_0067a150(2);
  uVar11 = 0;
  uVar10 = 0;
  uVar7 = 0xbf800000;
  uVar8 = param_5;
  fVar5 = (float10)FUN_004f90f0(uVar1,(float)param_2 - _DAT_008ed0e0,0xbf800000,param_5,0,0);
  fVar6 = (float)fVar5;
  fVar5 = (float10)FUN_004f90a0(uVar1,(float)param_1 - _DAT_008ed0e0,fVar6);
  puVar3 = (undefined4 *)FUN_00446360((float)fVar5,fVar6,uVar7,uVar8,uVar10,uVar11);
  *puVar2 = *puVar3;
  puVar2[1] = puVar3[1];
  puVar2[2] = puVar3[2];
  puVar2[3] = puVar3[3];
  puVar2[4] = puVar3[4];
  puVar2[5] = puVar3[5];
  puVar2 = puVar2 + 6;
  uVar10 = 0;
  uVar7 = 0;
  uVar8 = 0xbf800000;
  fVar5 = (float10)FUN_004f90f0(uVar1,(float)param_4 - _DAT_008ed0e0,0xbf800000,param_5,0,0);
  fVar6 = (float)fVar5;
  fVar5 = (float10)FUN_004f90a0(uVar1,(float)param_3 - _DAT_008ed0e0,fVar6);
  puVar3 = (undefined4 *)FUN_00446360((float)fVar5,fVar6,uVar8,param_5,uVar7,uVar10);
  *puVar2 = *puVar3;
  puVar2[1] = puVar3[1];
  puVar2[2] = puVar3[2];
  puVar2[3] = puVar3[3];
  puVar2[4] = puVar3[4];
  puVar2[5] = puVar3[5];
  puVar2 = puVar2 + 6;
  psVar4 = (short *)FUN_0067a1e0(2);
  *psVar4 = (short)uVar9;
  psVar4[1] = (short)uVar9 + 1;
  FUN_00679f10(uVar9,uVar1,puVar2,psVar4 + 2);
  FUN_0083e885();
  return;
}

