/*
 * Entry: 004f20bf
 * Name: Get_Closest_RGB_Entry
 * Namespace: Global
 * Signature: long Get_Closest_RGB_Entry(float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Get_Closest_RGB_Entry(float param_1,float param_2,float param_3)

{
  float fVar1;
  float fVar2;
  long in_ECX;
  float *pfVar3;
  int iVar4;
  long local_8;
  
  fVar1 = 1e+06;
  iVar4 = 0;
  pfVar3 = Float_Pal[0] + 1;
  local_8 = in_ECX;
  do {
    fVar2 = param_1 - (*(float (*) [3])(pfVar3 + -1))[0];
    fVar2 = (param_3 - pfVar3[1]) * (param_3 - pfVar3[1]) +
            (param_2 - *pfVar3) * (param_2 - *pfVar3) + fVar2 * fVar2;
    if (fVar2 < fVar1) {
      fVar1 = fVar2;
      local_8 = iVar4;
    }
    pfVar3 = pfVar3 + 3;
    iVar4 = iVar4 + 1;
  } while ((int)pfVar3 < 0xd3f184);
  return local_8;
}
