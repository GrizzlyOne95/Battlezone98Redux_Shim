/*
 * Entry: 004d0f07
 * Name: LightningFeature::SetBoltPos
 * Namespace: LightningFeature
 * Signature: void SetBoltPos(LightningFeature * this, BoltEmitter * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
LightningFeature::SetBoltPos(LightningFeature *this,BoltEmitter *param_1,CAMERA *param_2)

{
  float fVar1;
  float fVar2;
  _OBJ76 *p_Var3;
  double dVar4;
  
  fVar1 = (float)(((float10)param_2->View_Pyramid[2].x + (float10)param_2->View_Pyramid[1].x) *
                  (float10)0.5 - (float10)param_2->View_Pyramid[0].x);
  fVar2 = (float)(((float10)param_2->View_Pyramid[2].z + (float10)param_2->View_Pyramid[1].z) *
                  (float10)0.5 - (float10)param_2->View_Pyramid[0].z);
  dVar4 = rsqrt((double)(fVar1 * fVar1 + fVar2 * fVar2));
  p_Var3 = param_1->target;
  param_1->nx = -(fVar2 * (float)dVar4);
  param_1->nz = (float)dVar4 * fVar1;
  (param_1->origin).x = (float)(p_Var3->transform).posit_x;
  (param_1->origin).y = (float)param_2->View_Pyramid[0].y + 100.0;
  (param_1->origin).z = (float)(p_Var3->transform).posit_z;
  return;
}
