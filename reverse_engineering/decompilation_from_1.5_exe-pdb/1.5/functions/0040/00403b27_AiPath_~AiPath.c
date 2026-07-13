/*
 * Entry: 00403b27
 * Name: AiPath::~AiPath
 * Namespace: AiPath
 * Signature: void ~AiPath(AiPath * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiPath::~AiPath(AiPath *this)

{
  _Const_iterator<1> _Var1;
  AiPath *local_8;
  AiPath *pAStack_4;
  
  _Var1._Ptr = *(_Node **)&this->me;
  _Var1._padding_ = (int)&local_8;
  local_8 = this;
  pAStack_4 = this;
  std::list<AiPath_*,std::allocator<AiPath_*>_>::erase(&pathList,_Var1);
  if (this->label != (char *)0x0) {
    operator_delete__(this->label);
  }
  operator_delete__(this->points);
  return;
}
