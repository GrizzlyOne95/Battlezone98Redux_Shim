/*
 * Entry: 0045b0d4
 * Name: RecycleTask::InitGotoRepair
 * Namespace: RecycleTask
 * Signature: void InitGotoRepair(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::InitGotoRepair(RecycleTask *this)

{
  bool bVar1;
  GameObject *pGVar2;
  float *pfVar3;
  ScavGotoRepair *pSVar4;
  float10 fVar5;
  
  fVar5 = (float10)(**(code **)(this->me->_padding_ + 0x1c))();
  if ((float10)0.5 < fVar5) {
    this->nextState = 1;
    return;
  }
  pGVar2 = GetClosestObject((GameObject *)this->me,0x52444550,-1,22500.0);
  if ((pGVar2 != (GameObject *)0x0) &&
     (bVar1 = GameObject::EnemyP((GameObject *)this->me,pGVar2), !bVar1)) {
    pfVar3 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
    (this->where).x = *pfVar3;
    (this->where).y = pfVar3[1];
    (this->where).z = pfVar3[2];
    pSVar4 = operator_new(0x160);
    if (pSVar4 == (ScavGotoRepair *)0x0) {
      pSVar4 = (ScavGotoRepair *)0x0;
    }
    else {
      pSVar4 = ScavGotoRepair::ScavGotoRepair(pSVar4,this->me,pGVar2);
    }
    this->subtask = (AiTask *)pSVar4;
    return;
  }
  this->nextState = 1;
  return;
}
