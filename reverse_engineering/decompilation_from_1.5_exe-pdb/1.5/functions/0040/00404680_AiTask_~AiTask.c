/*
 * Entry: 00404680
 * Name: AiTask::~AiTask
 * Namespace: AiTask
 * Signature: void ~AiTask(AiTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiTask::~AiTask(AiTask *this)

{
  AiTask *local_8;
  
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  std::list<AiTask_*,std::allocator<AiTask_*>_>::remove(tasklist,&local_8);
  SObject::~SObject((SObject *)this);
  return;
}
