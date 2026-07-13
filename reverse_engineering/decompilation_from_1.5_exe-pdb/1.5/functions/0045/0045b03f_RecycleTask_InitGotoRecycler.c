/*
 * Entry: 0045b03f
 * Name: RecycleTask::InitGotoRecycler
 * Namespace: RecycleTask
 * Signature: void InitGotoRecycler(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::InitGotoRecycler(RecycleTask *this)

{
  Team *this_00;
  long lVar1;
  long lVar2;
  int iVar3;
  GameObject *this_01;
  ScavGotoDrop *pSVar4;
  
  this_00 = (Team *)this->me->_padding_;
  lVar1 = Team::GetScrap(this_00);
  lVar2 = Team::GetMaxScrap(this_00);
  if (lVar1 < lVar2) {
    iVar3 = (**(code **)(this->me->_padding_ + 4))();
    this_01 = GetClosestScrapDropoff((GameObject *)this->me);
    if (this_01 != (GameObject *)0x0) {
      foundDrop[iVar3] = true;
      iVar3 = GameObject::GetHandle(this_01);
      this->dropHandle = iVar3;
      pSVar4 = operator_new(0x160);
      if (pSVar4 == (ScavGotoDrop *)0x0) {
        pSVar4 = (ScavGotoDrop *)0x0;
      }
      else {
        pSVar4 = ScavGotoDrop::ScavGotoDrop(pSVar4,this->me,this_01);
      }
      this->subtask = (AiTask *)pSVar4;
      return;
    }
    if (foundDrop[iVar3] != false) {
      Say(this,this->noDropMsg);
      foundDrop[iVar3] = false;
    }
  }
  this->nextState = 6;
  return;
}
