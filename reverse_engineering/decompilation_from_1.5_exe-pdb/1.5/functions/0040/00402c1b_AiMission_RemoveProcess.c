/*
 * Entry: 00402c1b
 * Name: AiMission::RemoveProcess
 * Namespace: AiMission
 * Signature: void RemoveProcess(AiMission * this, AiProcess * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiMission::RemoveProcess(AiMission *this,AiProcess *param_1)

{
  std::list<AiProcess_*,std::allocator<AiProcess_*>_>::remove(&this->processes,&param_1);
  return;
}
