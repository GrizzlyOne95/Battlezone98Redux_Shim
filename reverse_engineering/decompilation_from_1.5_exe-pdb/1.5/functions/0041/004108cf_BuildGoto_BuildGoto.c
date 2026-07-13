/*
 * Entry: 004108cf
 * Name: BuildGoto::BuildGoto
 * Namespace: BuildGoto
 * Signature: BuildGoto * BuildGoto(BuildGoto * this, Craft * param_1, AiPath * param_2, GameObjectClass * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BuildGoto * __thiscall
BuildGoto::BuildGoto(BuildGoto *this,Craft *param_1,AiPath *param_2,GameObjectClass *param_3)

{
  float fVar1;
  SPHERE *pSVar2;
  
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2,true);
  this->buildStage = 0;
  this->_padding_ = (int)&_vftable_;
  this->buildClass = param_3;
  pSVar2 = GameObjectClass::GetBoundingSphere(param_3);
  fVar1 = pSVar2->radius + 10.0;
  this->buildDistSq = fVar1 * fVar1;
  Producer::StartBuild((Producer *)param_1,param_3);
  return this;
}
