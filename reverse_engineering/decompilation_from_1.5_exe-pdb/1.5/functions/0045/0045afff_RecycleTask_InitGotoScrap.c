/*
 * Entry: 0045afff
 * Name: RecycleTask::InitGotoScrap
 * Namespace: RecycleTask
 * Signature: void InitGotoScrap(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::InitGotoScrap(RecycleTask *this)

{
  GameObject *pGVar1;
  ScavGotoScrap *pSVar2;
  
  pGVar1 = GameObjectHandle::GetObj(this->scrapHandle);
  if (pGVar1 == (GameObject *)0x0) {
    this->nextState = 1;
  }
  else {
    pSVar2 = operator_new(0x160);
    if (pSVar2 == (ScavGotoScrap *)0x0) {
      pSVar2 = (ScavGotoScrap *)0x0;
    }
    else {
      pSVar2 = ScavGotoScrap::ScavGotoScrap(pSVar2,this->me,pGVar1);
    }
    this->subtask = (AiTask *)pSVar2;
  }
  return;
}
