/*
 * Entry: 00403971
 * Name: AiPath::AiPath
 * Namespace: AiPath
 * Signature: AiPath * AiPath(AiPath * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath * __thiscall AiPath::AiPath(AiPath *this)

{
  _Const_iterator<1> _Var1;
  _Iterator<1> _Var2;
  undefined1 local_18 [8];
  _Const_iterator<1> local_10;
  AiPath *local_8;
  
  *(undefined4 *)&this->me = 0;
  *(undefined4 *)&(this->me).field_0x4 = 0;
  local_8 = this;
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_10,pathList._Myhead,&pathList);
  _Var1._Ptr = (_Node *)local_10._padding_;
  _Var1._padding_ = (int)local_18;
  _Var2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::insert
                    (&pathList,_Var1,(AiPath **)local_10._Ptr);
  *(undefined4 *)&this->me = *_Var2._0_4_;
  *(undefined4 *)&(this->me).field_0x4 = _Var2._0_4_[1];
  this->bDontSave = false;
  return this;
}
