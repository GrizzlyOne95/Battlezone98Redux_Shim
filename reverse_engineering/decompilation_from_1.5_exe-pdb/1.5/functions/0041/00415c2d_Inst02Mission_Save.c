/*
 * Entry: 00415c2d
 * Name: Inst02Mission::Save
 * Namespace: Inst02Mission
 * Signature: bool Save(Inst02Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst02Mission::Save(Inst02Mission *this,_iobuf *param_1)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  AiProcess **ppAVar4;
  _Const_iterator<1> _Stack_18;
  _Const_iterator<1> _Stack_10;
  int iStack_8;
  
  bVar2 = ::out(param_1,"[AiMission]");
  if (missionSave == false) {
    iStack_8 = 0;
    piVar1 = &this->_padding_;
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&_Stack_18,*(_Node **)this->_padding_,
               (list<AiProcess_*,std::allocator<AiProcess_*>_> *)piVar1);
    _Stack_10._padding_ = _Stack_18._padding_;
    _Stack_10._Ptr = _Stack_18._Ptr;
    if (bVar2) {
      while( true ) {
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&_Stack_18,(_Node *)this->_padding_,
                   (list<AiProcess_*,std::allocator<AiProcess_*>_> *)piVar1);
        bVar2 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                          (&_Stack_10,&_Stack_18);
        if (bVar2) break;
        ppAVar4 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                            (&_Stack_10);
        if ((char)(*ppAVar4)->_padding_ == '\0') {
          iStack_8 = iStack_8 + 1;
        }
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++
                  (&_Stack_10);
      }
    }
    bVar2 = ::out(param_1,&iStack_8,4,"size");
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&_Stack_18,*(_Node **)this->_padding_,
               (list<AiProcess_*,std::allocator<AiProcess_*>_> *)piVar1);
    _Stack_10._padding_ = _Stack_18._padding_;
    _Stack_10._Ptr = _Stack_18._Ptr;
    if (bVar2) {
      do {
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&_Stack_18,(_Node *)this->_padding_,
                   (list<AiProcess_*,std::allocator<AiProcess_*>_> *)piVar1);
        bVar3 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                          (&_Stack_10,&_Stack_18);
        if (bVar3) break;
        ppAVar4 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                            (&_Stack_10);
        if (*(bool *)&(*ppAVar4)->_padding_ == false) {
          bVar2 = RtimeClass::Save(param_1,(SObject *)*ppAVar4);
        }
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++
                  (&_Stack_10);
      } while (bVar2 != false);
      if ((((bVar2 != false) && (bVar2 = ::out(param_1,(bool *)&this->_padding_,1,"done"), bVar2))
          && (bVar2 = ::out(param_1,(float *)&this->_padding_,4,"shutdownTime"), bVar2)) &&
         ((bVar2 = ::out(param_1,(bool *)&this->_padding_,1,"failed"), bVar2 &&
          (bVar2 = ::out(param_1,(char *)((int)&this->_padding_ + 1),0xe,"resultName"), bVar2)))) {
        return true;
      }
    }
    bVar2 = false;
  }
  return bVar2;
}
