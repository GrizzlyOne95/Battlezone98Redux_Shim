/*
 * Entry: 00459e92
 * Name: RecycleTask::DoWait
 * Namespace: RecycleTask
 * Signature: void DoWait(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::DoWait(RecycleTask *this)

{
  GameObject *pGVar1;
  float fVar2;
  
  pGVar1 = GetClosestScrapDropoff((GameObject *)this->me);
  if ((pGVar1 != (GameObject *)0x0) && (this->me[1]._padding_ <= this->me[1]._padding_)) {
    this->nextState = 3;
    return;
  }
  fVar2 = Get_TimeLocal();
  if (this->nextCheck < fVar2) {
    this->nextState = 1;
  }
  (this->me->vhcl->control).steer = 0.0;
  (this->me->vhcl->control).turbo = 0;
  (this->me->vhcl->control).braccel = 0.0;
  return;
}
