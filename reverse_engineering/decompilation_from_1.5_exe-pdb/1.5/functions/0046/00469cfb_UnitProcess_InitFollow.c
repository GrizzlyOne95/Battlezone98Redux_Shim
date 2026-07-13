/*
 * Entry: 00469cfb
 * Name: UnitProcess::InitFollow
 * Namespace: UnitProcess
 * Signature: void InitFollow(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitFollow(UnitProcess *this)

{
  VEHICLE *pVVar1;
  GameObject *pGVar2;
  FollowTask *pFVar3;
  
  pVVar1 = this->me->vhcl;
  (pVVar1->control).steer = 0.0;
  (pVVar1->control).pitch = 0.0;
  pGVar2 = GameObjectHandle::GetObj(this->whoHandle);
  pFVar3 = operator_new(0x138);
  if (pFVar3 == (FollowTask *)0x0) {
    pFVar3 = (FollowTask *)0x0;
  }
  else {
    pFVar3 = FollowTask::FollowTask(pFVar3,this->me,pGVar2);
  }
  this->task = (AiTask *)pFVar3;
  return;
}
