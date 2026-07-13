/*
 * Entry: 00457046
 * Name: PatrolTask::Patrol_New_Spot
 * Namespace: PatrolTask
 * Signature: int Patrol_New_Spot(PatrolTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall PatrolTask::Patrol_New_Spot(PatrolTask *this)

{
  int iVar1;
  AiPath *pAVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  VECTOR_3D *pVVar5;
  VECTOR_3D local_10;
  
  if ((char)this->_padding_ != '\0') {
    pAVar2 = (AiPath *)this->_padding_;
    if (pAVar2 != (AiPath *)0x0) {
      AiPath::Release(pAVar2);
      this->_padding_ = 0;
    }
  }
  iVar1 = Choose_Next_Spot(this,&local_10);
  iVar4 = 0;
  if (iVar1 != 0) {
    pAVar2 = operator_new(0x1c);
    if (pAVar2 == (AiPath *)0x0) {
      pAVar2 = (AiPath *)0x0;
    }
    else {
      pVVar5 = &local_10;
      pVVar3 = (VECTOR_3D *)(**(code **)(this->my_craft->_padding_ + 0xc))();
      pAVar2 = AiPath::AiPath(pAVar2,pVVar3,pVVar5);
    }
    this->_padding_ = (int)pAVar2;
    iVar4 = 1;
    this->_padding_ = 0;
    *(undefined1 *)&this->_padding_ = 1;
    this->_padding_ = 1;
    this->_padding_ = 1;
  }
  return iVar4;
}
