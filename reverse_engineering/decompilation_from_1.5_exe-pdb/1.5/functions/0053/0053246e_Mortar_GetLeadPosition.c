/*
 * Entry: 0053246e
 * Name: Mortar::GetLeadPosition
 * Namespace: Mortar
 * Signature: bool GetLeadPosition(Mortar * this, VECTOR_3D * param_1, float * param_2, VECTOR_3D * param_3, bool param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Mortar::GetLeadPosition
          (Mortar *this,VECTOR_3D *param_1,float *param_2,VECTOR_3D *param_3,bool param_4)

{
  bool bVar1;
  float *extraout_EDX;
  
  bVar1 = GetImpactTimeSq(this,param_2,param_3,param_4);
  param_1->x = *extraout_EDX;
  param_1->y = *param_2 * 4.9 + extraout_EDX[1];
  param_1->z = extraout_EDX[2];
  return bVar1;
}
