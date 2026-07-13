
void FUN_006869c0(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  short *psVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  float fVar12;
  
  if ((DAT_02b79b34 != 0) && (cVar1 = FUN_0048efc0(), cVar1 != '\0')) {
    FUN_00684c80(1);
    FUN_00684c60(1);
    uVar10 = 4;
    uVar11 = DAT_00920ef4;
    uVar3 = FUN_00684bf0(4,DAT_00920ef4);
    FUN_00679d70(uVar3,uVar10,uVar11);
    FUN_0067a110(4,6);
    sVar2 = FUN_00684c10();
    uVar11 = DAT_02b79b2c;
    fVar7 = (float10)FUN_004f90a0(DAT_02b79b2c,(float)param_1 - DAT_00920e9c);
    fVar8 = (float10)FUN_004f90a0(uVar11,(float)param_3 - DAT_00920e9c);
    fVar9 = (float10)FUN_004f90f0(uVar11,(float)param_2 - DAT_00920e9c);
    fVar12 = (float)fVar9;
    fVar9 = (float10)FUN_004f90f0(uVar11,(float)param_4 - DAT_00920e9c,fVar12);
    puVar4 = (undefined4 *)FUN_0067a150(4);
    puVar5 = (undefined4 *)FUN_00446360((float)fVar7,fVar12,0xbf800000,param_5,0,0);
    *puVar4 = *puVar5;
    puVar4[1] = puVar5[1];
    puVar4[2] = puVar5[2];
    puVar4[3] = puVar5[3];
    puVar4[4] = puVar5[4];
    puVar4[5] = puVar5[5];
    puVar5 = (undefined4 *)FUN_00446360((float)fVar8,fVar12,0xbf800000,param_5,0x3f800000,0);
    puVar4[6] = *puVar5;
    puVar4[7] = puVar5[1];
    puVar4[8] = puVar5[2];
    puVar4[9] = puVar5[3];
    puVar4[10] = puVar5[4];
    puVar4[0xb] = puVar5[5];
    puVar5 = (undefined4 *)
             FUN_00446360((float)fVar8,(float)fVar9,0xbf800000,param_5,0x3f800000,0x3f800000);
    puVar4[0xc] = *puVar5;
    puVar4[0xd] = puVar5[1];
    puVar4[0xe] = puVar5[2];
    puVar4[0xf] = puVar5[3];
    puVar4[0x10] = puVar5[4];
    puVar4[0x11] = puVar5[5];
    puVar5 = (undefined4 *)FUN_00446360((float)fVar7,(float)fVar9,0xbf800000,param_5,0,0x3f800000);
    puVar4[0x12] = *puVar5;
    puVar4[0x13] = puVar5[1];
    puVar4[0x14] = puVar5[2];
    puVar4[0x15] = puVar5[3];
    puVar4[0x16] = puVar5[4];
    puVar4[0x17] = puVar5[5];
    psVar6 = (short *)FUN_0067a1e0(6);
    *psVar6 = sVar2;
    psVar6[1] = sVar2 + 2;
    psVar6[2] = sVar2 + 1;
    psVar6[3] = sVar2;
    psVar6[4] = sVar2 + 3;
    psVar6[5] = sVar2 + 2;
    FUN_00679f10();
  }
  FUN_0083e885();
  return;
}

