/*
 * Entry: 00402c0b
 * Name: AiMission::AddProcess
 * Namespace: AiMission
 * Signature: void AddProcess(AiMission * this, AiProcess * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiMission::AddProcess(AiMission *this,AiProcess *param_1)

{
  std::list<AiProcess_*,std::allocator<AiProcess_*>_>::push_back(&this->processes,&param_1);
  return;
}
