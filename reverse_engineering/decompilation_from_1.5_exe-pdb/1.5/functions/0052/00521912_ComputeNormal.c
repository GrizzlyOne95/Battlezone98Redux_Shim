/*
 * Entry: 00521912
 * Name: ComputeNormal
 * Namespace: Global
 * Signature: void ComputeNormal(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ComputeNormal(long param_1,long param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  uchar extraout_AL;
  uchar *puVar4;
  uchar uVar5;
  int unaff_EBX;
  int unaff_ESI;
  int unaff_EDI;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  
  fVar12 = GetTerrainHeight(unaff_EDI,unaff_ESI);
  fVar13 = GetTerrainHeight(unaff_EDI + -1,unaff_ESI + -1);
  fVar14 = GetTerrainHeight(unaff_EDI,unaff_ESI + -1);
  dVar25 = (double)(fVar14 - fVar12);
  fVar15 = GetTerrainHeight(unaff_EDI + 1,unaff_ESI);
  dVar1 = (double)(fVar15 - fVar12);
  fVar16 = GetTerrainHeight(unaff_EDI + 1,unaff_ESI + 1);
  fVar17 = GetTerrainHeight(unaff_EDI,unaff_ESI + 1);
  dVar2 = (double)(fVar17 - fVar12);
  fVar18 = GetTerrainHeight(unaff_EDI + -1,unaff_ESI);
  fVar18 = fVar18 - fVar12;
  dVar24 = (double)fVar18;
  dVar3 = dVar25 - (double)(fVar13 - fVar12);
  dVar19 = rsqrt(dVar3 * dVar3 + dVar25 * dVar25 + 1.0);
  dVar20 = rsqrt(dVar1 * dVar1 + dVar25 * dVar25 + 1.0);
  dVar25 = (double)(fVar16 - fVar12) - dVar1;
  dVar21 = rsqrt(dVar25 * dVar25 + dVar1 * dVar1 + 1.0);
  dVar1 = (double)(fVar16 - fVar12) - dVar2;
  dVar22 = rsqrt(dVar1 * dVar1 + dVar2 * dVar2 + 1.0);
  dVar23 = rsqrt(dVar24 * dVar24 + dVar2 * dVar2 + 1.0);
  dVar2 = dVar24 - (double)(fVar13 - fVar12);
  dVar24 = rsqrt(dVar2 * dVar2 + dVar24 * dVar24 + 1.0);
  fVar6 = (float10)dVar21;
  fVar7 = (float10)dVar20;
  fVar8 = (float10)dVar22;
  fVar9 = (float10)dVar19;
  fVar10 = (float10)dVar23;
  fVar11 = (((fVar6 + fVar7) * (float10)(fVar15 - fVar12) + (float10)dVar1 * fVar8 +
            (float10)dVar3 * fVar9) - (float10)fVar18 * fVar10) - (float10)dVar24 * (float10)fVar18;
  fVar18 = (float)fVar11;
  fVar13 = (float)(((((fVar9 - fVar7) - fVar6) - fVar8) - fVar10) - (float10)dVar24);
  fVar6 = (fVar10 + fVar8) * (float10)(fVar17 - fVar12) +
          ((float10)dVar2 * (float10)dVar24 - (fVar7 + fVar9) * (float10)(fVar14 - fVar12)) +
          (float10)dVar25 * fVar6;
  dVar25 = rsqrt((double)((float10)fVar13 * (float10)fVar13 + fVar6 * fVar6 + fVar11 * fVar11));
  dVar25 = -(((double)Sun_Light.x * (double)fVar18 +
             (double)Sun_Light.y * (double)fVar13 + (double)Sun_Light.z * (double)(float)fVar6) *
            dVar25);
  if (0.00390625 <= dVar25) {
    if (dVar25 <= 0.99609375) {
      _ftol2_sse();
      uVar5 = extraout_AL;
    }
    else {
      uVar5 = 0xff;
    }
  }
  else {
    uVar5 = '\0';
  }
  puVar4 = GetNormalPtr(unaff_EBX,(int)fVar18);
  *puVar4 = uVar5;
  return;
}
