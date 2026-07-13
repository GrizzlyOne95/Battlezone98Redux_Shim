/*
 * Entry: 0048545c
 * Name: ConstructionDisplay::SetBox
 * Namespace: ConstructionDisplay
 * Signature: void SetBox(ConstructionDisplay * this, BBOX * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionDisplay::SetBox(ConstructionDisplay *this,BBOX *param_1,MAT_3D *param_2)

{
  VECTOR_3D *pVVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = (param_1->min).z;
  pVVar1 = this->corner;
  pVVar1->x = (param_1->min).x;
  this->corner[0].y = 0.5;
  this->corner[0].z = fVar3;
  fVar3 = (param_1->max).z;
  this->corner[1].x = (param_1->min).x;
  this->corner[1].y = 0.5;
  this->corner[1].z = fVar3;
  fVar3 = (param_1->max).z;
  this->corner[2].x = (param_1->max).x;
  this->corner[2].y = 0.5;
  this->corner[2].z = fVar3;
  fVar3 = (param_1->min).z;
  this->corner[3].x = (param_1->max).x;
  this->corner[3].y = 0.5;
  this->corner[3].z = fVar3;
  fVar3 = (param_1->max).z;
  fVar2 = (param_1->min).z;
  this->corner[4].x = ((param_1->min).x + (param_1->max).x) * 0.5;
  this->corner[4].y = 0.0;
  this->corner[4].z = (fVar3 + fVar2) * 0.5;
  fVar3 = max<float>((param_1->max).x - (param_1->min).x,(param_1->max).z - (param_1->min).z);
  this->radius = fVar3 * 0.5;
  Vector_Transform(pVVar1,pVVar1,5,param_2);
  return;
}
