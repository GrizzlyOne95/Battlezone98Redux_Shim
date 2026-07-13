/*
 * Entry: 00402ed9
 * Name: AiMission::~AiMission
 * Namespace: AiMission
 * Signature: void ~AiMission(AiMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiMission::~AiMission(AiMission *this)

{
  uint uVar1;
  AiProcess **ppAVar2;
  
  uVar1 = (this->processes)._Mysize;
  this->_padding_ = (int)&_vftable_;
  if (uVar1 != 0) {
    do {
      ppAVar2 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::back(&this->processes);
      if (*ppAVar2 != (AiProcess *)0x0) {
        (**(code **)(*ppAVar2)->_padding_)(1);
      }
    } while ((this->processes)._Mysize != 0);
  }
  AiTask::PostRun();
  AISchedule_PostRun();
  if (current == this) {
    current = (AiMission *)0x0;
  }
  std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Tidy(&this->processes);
  operator_delete((void *)(this->processes)._padding_);
  SObject::~SObject((SObject *)this);
  return;
}
