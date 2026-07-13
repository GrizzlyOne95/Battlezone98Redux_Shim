/*
 * Entry: 004690bb
 * Name: UnitProcess::InitPatrol
 * Namespace: UnitProcess
 * Signature: void InitPatrol(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitPatrol(UnitProcess *this)

{
  Craft *pCVar1;
  VEHICLE *pVVar2;
  AiPath *pAVar3;
  AiTask *pAVar4;
  
  pCVar1 = this->me;
  pVVar2 = pCVar1->vhcl;
  pAVar3 = this->where;
  (pVVar2->control).steer = 0.0;
  (pVVar2->control).pitch = 0.0;
  pAVar4 = PatrolTask_Build(pCVar1,pAVar3,PERIMETER);
  this->task = pAVar4;
  return;
}
