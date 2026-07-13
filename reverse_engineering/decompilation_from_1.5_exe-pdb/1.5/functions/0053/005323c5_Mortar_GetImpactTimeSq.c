/*
 * Entry: 005323c5
 * Name: Mortar::GetImpactTimeSq
 * Namespace: Mortar
 * Signature: bool GetImpactTimeSq(Mortar * this, float * param_1, VECTOR_3D * param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Mortar::GetImpactTimeSq(Mortar *this,float *param_1,VECTOR_3D *param_2,bool param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = *(float *)(*(int *)&this->field_0xc + 0x50);
  fVar3 = param_2->x - (float)*(double *)&this->field_0x48;
  fVar2 = param_2->y - (float)*(double *)&this->field_0x50;
  fVar4 = param_2->z - (float)*(double *)&this->field_0x58;
  fVar4 = fVar4 * fVar4 + fVar3 * fVar3;
  fVar3 = (fVar2 * fVar2) / fVar4 + 1.0;
  fVar1 = fVar1 * fVar1 - fVar2 * 9.8;
  fVar2 = fVar1 * fVar1 - fVar4 * 24.01 * fVar3 * 4.0;
  if (0.0 < fVar2) {
    if (param_3) {
      fVar1 = SQRT(fVar2) + fVar1;
    }
    else {
      fVar1 = fVar1 - SQRT(fVar2);
    }
  }
  *param_1 = fVar4 / (fVar1 / (fVar3 + fVar3));
  return 0.0 <= fVar2;
}
