/*
 * Entry: 00508859
 * Name: AI_Match_Get_Unit_Type_Strength
 * Namespace: Global
 * Signature: float AI_Match_Get_Unit_Type_Strength(tagUNITTYPE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl AI_Match_Get_Unit_Type_Strength(tagUNITTYPE *param_1)

{
  float fVar1;
  int local_c;
  int local_8;
  
  AI_Match_Get_Weapon_Details(param_1,&local_c,&local_8);
  fVar1 = (float)local_c;
  if (0 < local_8) {
    fVar1 = fVar1 / (float)local_8;
  }
  return fVar1;
}
