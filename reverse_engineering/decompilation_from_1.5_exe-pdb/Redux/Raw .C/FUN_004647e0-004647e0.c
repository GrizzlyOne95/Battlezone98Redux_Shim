
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004647e0(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  float10 fVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  fVar8 = (float10)FUN_00462470();
  fVar9 = (float10)FUN_00462470();
  fVar10 = ((float)fVar8 + (float)fVar9) * _DAT_008e7938;
  pfVar7 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  fVar13 = *pfVar7;
  fVar1 = pfVar7[2];
  pfVar7 = (float *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
  fVar2 = *pfVar7;
  fVar3 = pfVar7[2];
  pfVar7 = (float *)FUN_004624b0();
  fVar12 = *pfVar7;
  fVar4 = pfVar7[2];
  pfVar7 = (float *)FUN_004624b0();
  fVar5 = *pfVar7;
  fVar6 = pfVar7[2];
  if (0.0 < (fVar12 - fVar5) * (fVar2 - fVar13) + (fVar4 - fVar6) * (fVar3 - fVar1)) {
    fVar11 = (((fVar12 * fVar12 + fVar5 * fVar5) - fVar12 * 2.0 * fVar5) + fVar4 * fVar4 +
             fVar6 * fVar6) - fVar4 * 2.0 * fVar6;
    fVar12 = (((((fVar13 * 2.0 * fVar12 - fVar13 * 2.0 * fVar5) - fVar2 * 2.0 * fVar12) +
                fVar2 * 2.0 * fVar5 + fVar1 * 2.0 * fVar4) - fVar1 * 2.0 * fVar6) -
             fVar3 * 2.0 * fVar4) + fVar3 * 2.0 * fVar6;
    fVar13 = fVar12 * fVar12 -
             fVar11 * 4.0 *
             (((((fVar13 * fVar13 - fVar13 * 2.0 * fVar2) + fVar2 * fVar2 + fVar1 * fVar1) -
               fVar1 * 2.0 * fVar3) + fVar3 * fVar3) - fVar10 * fVar10);
    if ((fVar11 != 0.0) && (0.0 <= fVar13)) {
      FUN_00417910(fVar13);
    }
  }
  FUN_0083e885();
  return;
}

