/*
 * Entry: 004f24f9
 * Name: Device_Build_ColorRamp_Entry
 * Namespace: Global
 * Signature: void Device_Build_ColorRamp_Entry(VIDEO_DEVICE * param_1, long param_2, float param_3, float param_4, float param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Device_Build_ColorRamp_Entry
          (VIDEO_DEVICE *param_1,long param_2,float param_3,float param_4,float param_5,
          float param_6)

{
  uchar uVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int in_EAX;
  int iVar10;
  float extraout_EAX;
  long lVar11;
  float fVar12;
  int unaff_ESI;
  uchar *puVar13;
  float10 extraout_ST0;
  float10 fVar14;
  float10 fVar15;
  
  fVar5 = param_4 * 31.0;
  fVar6 = 1.0 / fVar5;
  fVar9 = (float)*(byte *)((unaff_ESI + 0x3c) * 3 + in_EAX) * 0.003921569 - (float)param_1;
  iVar10 = in_EAX + unaff_ESI * 3;
  fVar8 = (float)*(byte *)(iVar10 + 0xb5) * 0.003921569 - (float)param_2;
  param_4 = 0.0;
  fVar7 = (float)*(byte *)(iVar10 + 0xb6) * 0.003921569 - param_3;
  _ftol2_sse();
  fVar14 = extraout_ST0;
  if (0 < (int)extraout_EAX) {
    puVar13 = Luminance_Table[0x1f] + unaff_ESI;
    fVar12 = extraout_EAX;
    do {
      lVar11 = Get_Closest_RGB_Entry((float)param_1,(float)param_2,param_3);
      *puVar13 = (uchar)lVar11;
      param_1 = (VIDEO_DEVICE *)(fVar9 * fVar6 + (float)param_1);
      puVar13 = puVar13 + -0x100;
      fVar12 = (float)((int)fVar12 + -1);
      param_2 = (long)(fVar8 * fVar6 + (float)param_2);
      param_3 = fVar7 * fVar6 + param_3;
    } while (fVar12 != 0.0);
    fVar14 = (float10)1;
    param_4 = extraout_EAX;
  }
  fVar15 = fVar14 / ((float10)42.0 - (float10)fVar5);
  fVar2 = (float10)(float)param_1;
  fVar3 = (float10)(float)param_2;
  fVar4 = (float10)param_3;
  if ((int)param_4 < 0x20) {
    puVar13 = Luminance_Table[0x1f - (int)param_4] + unaff_ESI;
    iVar10 = 0x20 - (int)param_4;
    do {
      lVar11 = Get_Closest_RGB_Entry((float)param_1,(float)param_2,param_3);
      *puVar13 = (uchar)lVar11;
      param_1 = (VIDEO_DEVICE *)((float)((fVar14 - fVar2) * fVar15) + (float)param_1);
      puVar13 = puVar13 + -0x100;
      iVar10 = iVar10 + -1;
      param_2 = (long)((float)((fVar14 - fVar3) * fVar15) + (float)param_2);
      param_3 = (float)((fVar14 - fVar4) * fVar15) + param_3;
    } while (iVar10 != 0);
  }
  uVar1 = Luminance_Table[0x1f][unaff_ESI];
  iVar10 = 0x70;
  puVar13 = &DAT_00d20480 + unaff_ESI;
  do {
    *puVar13 = uVar1;
    puVar13 = puVar13 + 0x100;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  uVar1 = Luminance_Table[0][unaff_ESI];
  puVar13 = &DAT_00d2e380 + unaff_ESI;
  iVar10 = 0x70;
  do {
    *puVar13 = uVar1;
    puVar13 = puVar13 + -0x100;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  return;
}
