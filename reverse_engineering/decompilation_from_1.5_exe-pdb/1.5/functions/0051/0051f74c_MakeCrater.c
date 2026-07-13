/*
 * Entry: 0051f74c
 * Name: MakeCrater
 * Namespace: Global
 * Signature: long MakeCrater(float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl MakeCrater(float param_1,float param_2,float param_3)

{
  byte *pbVar1;
  uchar *puVar2;
  int unaff_ESI;
  int unaff_EDI;
  
  if (TerrainEdit != 0) {
    return 0;
  }
  _ftol2_sse();
  _ftol2_sse();
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 1;
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 2;
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 1;
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 2;
  puVar2 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *puVar2 = '\0';
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 2;
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 1;
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 2;
  pbVar1 = GetNormalPtr(unaff_EDI,unaff_ESI);
  *pbVar1 = *pbVar1 >> 1;
  return 1;
}
