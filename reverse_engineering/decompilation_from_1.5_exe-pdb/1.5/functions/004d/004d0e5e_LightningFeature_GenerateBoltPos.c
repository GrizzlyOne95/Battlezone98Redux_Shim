/*
 * Entry: 004d0e5e
 * Name: LightningFeature::GenerateBoltPos
 * Namespace: LightningFeature
 * Signature: void GenerateBoltPos(LightningFeature * this, BoltEmitter * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
LightningFeature::GenerateBoltPos(LightningFeature *this,BoltEmitter *param_1,CAMERA *param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = (float)(((float10)param_2->View_Pyramid[2].x + (float10)param_2->View_Pyramid[1].x) *
                  (float10)0.5 - (float10)param_2->View_Pyramid[0].x);
  fVar1 = (float)(((float10)param_2->View_Pyramid[2].z + (float10)param_2->View_Pyramid[1].z) *
                  (float10)0.5 - (float10)param_2->View_Pyramid[0].z);
  dVar3 = rsqrt((double)(fVar2 * fVar2 + fVar1 * fVar1));
  param_1->nx = -(fVar1 * (float)dVar3);
  param_1->nz = (float)dVar3 * fVar2;
  fVar2 = Random();
  (param_1->origin).x = fVar2 * BoltSet.distance + (float)param_2->View_Pyramid[0].x;
  (param_1->origin).y = (float)param_2->View_Pyramid[0].y + 100.0;
  fVar2 = Random();
  (param_1->origin).z = fVar2 * BoltSet.distance + (float)param_2->View_Pyramid[0].z;
  return;
}
