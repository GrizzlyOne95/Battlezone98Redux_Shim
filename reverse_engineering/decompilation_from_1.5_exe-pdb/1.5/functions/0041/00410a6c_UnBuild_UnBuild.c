/*
 * Entry: 00410a6c
 * Name: UnBuild::UnBuild
 * Namespace: UnBuild
 * Signature: UnBuild * UnBuild(UnBuild * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UnBuild * __thiscall UnBuild::UnBuild(UnBuild *this,Craft *param_1,GameObject *param_2)

{
  SPHERE *pSVar1;
  float fVar2;
  
  GoNear::GoNear((GoNear *)this,param_1,param_2,100.0);
  this->unbuildStage = 0;
  this->_padding_ = (int)&_vftable_;
  if (param_2 != (GameObject *)0x0) {
    pSVar1 = GameObject::GetSphere(param_2);
    fVar2 = Max(param_2->collisionRadius,pSVar1->radius);
    this->_padding_ = (int)((fVar2 + 20.0) * (fVar2 + 20.0));
  }
  return this;
}
