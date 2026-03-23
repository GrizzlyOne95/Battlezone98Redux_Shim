
void FUN_0077d7c0(float *param_1,int param_2,int param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  float fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  
  fVar8 = (float10)FUN_0077d410(param_2,param_3);
  dVar17 = (double)fVar8;
  fVar8 = (float10)FUN_0077d410(param_2 + -1,param_3 + -1);
  dVar12 = (double)fVar8 - dVar17;
  fVar8 = (float10)FUN_0077d410(param_2,param_3 + -1);
  dVar13 = (double)fVar8 - dVar17;
  fVar8 = (float10)FUN_0077d410(param_2 + 1,param_3);
  dVar14 = (double)fVar8 - dVar17;
  fVar8 = (float10)FUN_0077d410(param_2 + 1,param_3 + 1);
  dVar15 = (double)fVar8 - dVar17;
  fVar8 = (float10)FUN_0077d410(param_2,param_3 + 1);
  dVar16 = (double)fVar8 - dVar17;
  fVar8 = (float10)FUN_0077d410(param_2 + -1,param_3);
  dVar17 = (double)fVar8 - dVar17;
  fVar8 = (float10)FUN_00820570((dVar13 - dVar12) * (dVar13 - dVar12) + dVar13 * dVar13 + 1.0);
  dVar1 = (double)fVar8;
  fVar8 = (float10)FUN_00820570(dVar14 * dVar14 + dVar13 * dVar13 + 1.0);
  dVar2 = (double)fVar8;
  fVar8 = (float10)FUN_00820570(dVar14 * dVar14 + (dVar15 - dVar14) * (dVar15 - dVar14) + 1.0);
  dVar3 = (double)fVar8;
  fVar8 = (float10)FUN_00820570((dVar15 - dVar16) * (dVar15 - dVar16) + dVar16 * dVar16 + 1.0);
  dVar4 = (double)fVar8;
  fVar8 = (float10)FUN_00820570(dVar17 * dVar17 + dVar16 * dVar16 + 1.0);
  dVar5 = (double)fVar8;
  fVar8 = (float10)FUN_00820570(dVar17 * dVar17 + (dVar17 - dVar12) * (dVar17 - dVar12) + 1.0);
  dVar6 = (double)fVar8;
  fVar9 = (float)((((dVar13 - dVar12) * dVar1 + dVar14 * dVar2 + dVar14 * dVar3 +
                   (dVar15 - dVar16) * dVar4) - dVar17 * dVar5) - dVar17 * dVar6);
  fVar10 = (float)(((((dVar1 - dVar2) - dVar3) - dVar4) - dVar5) - dVar6);
  fVar11 = (float)((-dVar13 * dVar1 - dVar13 * dVar2) + (dVar15 - dVar14) * dVar3 + dVar16 * dVar4 +
                   dVar16 * dVar5 + (dVar17 - dVar12) * dVar6);
  fVar8 = (float10)FUN_00820570((double)(fVar9 * fVar9 + fVar10 * fVar10 + fVar11 * fVar11));
  fVar7 = -(float)fVar8;
  *param_1 = fVar9 * fVar7;
  param_1[1] = fVar10 * fVar7;
  param_1[2] = fVar11 * fVar7;
  FUN_0083e885();
  return;
}

