/*
 * Entry: 004046cb
 * Name: AiTask::AiTask
 * Namespace: AiTask
 * Signature: AiTask * AiTask(AiTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask * __thiscall AiTask::AiTask(AiTask *this)

{
  list<AiTask_*,std::allocator<AiTask_*>_> *this_00;
  AiTask *local_8;
  
  local_8 = this;
  SObject::SObject((SObject *)this);
  this->user = 0;
  this->_padding_ = (int)&_vftable_;
  if (tasklist == (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0) {
    this_00 = operator_new(0x1c);
    if (this_00 == (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0) {
      tasklist = (list<AiTask_*,std::allocator<AiTask_*>_> *)0x0;
    }
    else {
      tasklist = std::list<AiTask_*,std::allocator<AiTask_*>_>::
                 list<AiTask_*,std::allocator<AiTask_*>_>(this_00);
    }
  }
  local_8 = this;
  std::list<AiTask_*,std::allocator<AiTask_*>_>::push_back(tasklist,&local_8);
  return this;
}
