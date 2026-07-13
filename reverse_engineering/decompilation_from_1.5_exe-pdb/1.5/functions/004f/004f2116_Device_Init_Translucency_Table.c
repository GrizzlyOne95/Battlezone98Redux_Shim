/*
 * Entry: 004f2116
 * Name: Device_Init_Translucency_Table
 * Namespace: Global
 * Signature: void Device_Init_Translucency_Table(VIDEO_DEVICE * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Device_Init_Translucency_Table(VIDEO_DEVICE *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uchar *puVar5;
  uchar (*pauVar6) [256];
  long lVar7;
  float *pfVar8;
  float *pfVar9;
  uchar *local_8;
  
  Device_Init_Chrome_Key_Table(param_1);
  puVar5 = &param_1->Palette[0].g;
  pfVar8 = Float_Pal[0] + 1;
  do {
    (*(float (*) [3])(pfVar8 + -1))[0] = (float)((RGB *)(puVar5 + -1))->r * 0.003921569;
    *pfVar8 = (float)*puVar5 * 0.003921569;
    pfVar9 = pfVar8 + 3;
    pfVar8[1] = (float)puVar5[1] * 0.003921569;
    puVar5 = puVar5 + 3;
    pfVar8 = pfVar9;
  } while ((int)pfVar9 < 0xd3f184);
  if (param_2 < 0.0) {
    param_2 = 0.0;
  }
  if (1.0 < param_2) {
    param_2 = 1.0;
  }
  fVar4 = 1.0 - param_2;
  pauVar6 = Translucency_Table;
  pfVar8 = Float_Pal[0] + 1;
  do {
    pfVar9 = Float_Pal[0] + 1;
    fVar1 = (*(float (*) [3])(pfVar8 + -1))[0];
    fVar2 = *pfVar8;
    fVar3 = pfVar8[1];
    local_8 = *pauVar6;
    do {
      lVar7 = Get_Closest_RGB_Entry
                        ((*(float (*) [3])(pfVar9 + -1))[0] * param_2 + fVar1 * fVar4,
                         param_2 * *pfVar9 + fVar2 * fVar4,pfVar9[1] * param_2 + fVar3 * fVar4);
      pfVar9 = pfVar9 + 3;
      pauVar6 = (uchar (*) [256])(local_8 + 1);
      *local_8 = (uchar)lVar7;
      local_8 = (uchar *)pauVar6;
    } while ((int)pfVar9 < 0xd3f184);
    pfVar8 = pfVar8 + 3;
  } while ((int)pfVar8 < 0xd3f184);
  return;
}
