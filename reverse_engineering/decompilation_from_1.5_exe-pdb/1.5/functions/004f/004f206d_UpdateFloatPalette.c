/*
 * Entry: 004f206d
 * Name: UpdateFloatPalette
 * Namespace: Global
 * Signature: void UpdateFloatPalette(RGB * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateFloatPalette(RGB *param_1)

{
  byte bVar1;
  uchar *puVar2;
  float *pfVar3;
  float *pfVar4;
  
  puVar2 = &param_1->b;
  pfVar3 = Float_Pal[0] + 1;
  do {
    (*(float (*) [3])(pfVar3 + -1))[0] = (float)((RGB *)(puVar2 + -2))->r * 0.003921569;
    *pfVar3 = (float)puVar2[-1] * 0.003921569;
    bVar1 = *puVar2;
    pfVar4 = pfVar3 + 3;
    puVar2 = puVar2 + 3;
    pfVar3[1] = (float)bVar1 * 0.003921569;
    pfVar3 = pfVar4;
  } while ((int)pfVar4 < 0xd3f184);
  return;
}
