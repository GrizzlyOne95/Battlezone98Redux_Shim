/*
 * Entry: 005324a2
 * Name: Mortar::GetLeadPosition
 * Namespace: Mortar
 * Signature: bool GetLeadPosition(Mortar * this, VECTOR_3D * param_1, float * param_2, GameObject * param_3, bool param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Mortar::GetLeadPosition
          (Mortar *this,VECTOR_3D *param_1,float *param_2,GameObject *param_3,bool param_4)

{
  bool bVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D local_10;
  
  bVar1 = param_4;
  pVVar2 = (VECTOR_3D *)(**(code **)(param_3->_padding_ + 0xc))();
  bVar1 = GetLeadPosition(this,param_1,param_2,pVVar2,bVar1);
  if (param_4) {
    pVVar2 = AddMultVectors(&local_10,*param_1,SQRT(*param_2),(param_3->euler).v);
    param_1->x = pVVar2->x;
    param_1->y = pVVar2->y;
    param_1->z = pVVar2->z;
  }
  return bVar1;
}
