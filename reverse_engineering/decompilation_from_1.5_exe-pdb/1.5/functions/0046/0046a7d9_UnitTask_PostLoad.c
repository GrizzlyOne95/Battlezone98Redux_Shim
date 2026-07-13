/*
 * Entry: 0046a7d9
 * Name: UnitTask::PostLoad
 * Namespace: UnitTask
 * Signature: bool PostLoad(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitTask::PostLoad(UnitTask *this)

{
  GameObject *pGVar1;
  AiPath *pAVar2;
  bool bVar3;
  int iVar4;
  AttackGroup *this_00;
  FollowGroup *this_01;
  float fVar5;
  
  iVar4 = ConvertHandle(this->himHandle);
  this->himHandle = iVar4;
  iVar4 = ConvertHandle(this->saveHandle);
  this->saveHandle = iVar4;
  iVar4 = ConvertHandle(this->avoidSkip);
  this->avoidSkip = iVar4;
  if (this->nextStuck == 0.0) {
    fVar5 = Get_Time();
    this->nextStuck = fVar5;
  }
  bVar3 = SObject::PostLoad((SObject *)this);
  pGVar1 = (GameObject *)this->attackGroup;
  if (pGVar1 != (GameObject *)0x0) {
    this_00 = AttackGroup::Find(pGVar1);
    this->attackGroup = this_00;
    AttackGroup::Join(this_00,(GameObject *)this->me,this);
    this->him = (GameObject *)0x0;
  }
  pGVar1 = (GameObject *)this->followGroup;
  if (pGVar1 != (GameObject *)0x0) {
    this_01 = FollowGroup::Find(pGVar1);
    this->followGroup = this_01;
    FollowGroup::Join(this_01,(GameObject *)this->me);
    this->him = (GameObject *)0x0;
  }
  this->fixPoint = this->planPoint;
  pAVar2 = this->plan;
  if (pAVar2 != (AiPath *)0x0) {
    (this->goalPoint).x = pAVar2->points[pAVar2->pointCount + -1].x;
    fVar5 = pAVar2->points[pAVar2->pointCount + -1].z;
    (this->goalPoint).z = fVar5;
    fVar5 = Terrain_FindFloor((double)(this->goalPoint).x,(double)fVar5);
    (this->goalPoint).y = fVar5;
  }
  (**(code **)(this->_padding_ + 0x14))();
  return bVar3;
}
