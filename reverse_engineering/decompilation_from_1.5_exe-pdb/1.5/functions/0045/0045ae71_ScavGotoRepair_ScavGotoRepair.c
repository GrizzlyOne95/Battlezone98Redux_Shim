/*
 * Entry: 0045ae71
 * Name: ScavGotoRepair::ScavGotoRepair
 * Namespace: ScavGotoRepair
 * Signature: ScavGotoRepair * ScavGotoRepair(ScavGotoRepair * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavGotoRepair * __thiscall
ScavGotoRepair::ScavGotoRepair(ScavGotoRepair *this,Craft *param_1,GameObject *param_2)

{
  SPHERE *pSVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = 40.0;
  pSVar1 = GameObject::GetSphere(param_2);
  fVar2 = Max(param_2->collisionRadius,pSVar1->radius);
  fVar2 = Max(fVar2 + 15.0,fVar3);
  GoNear::GoNear((GoNear *)this,param_1,param_2,fVar2);
  *(undefined4 *)&this->field_0x100 = 0x40a00000;
  *(undefined ***)this = &_vftable_;
  return this;
}
