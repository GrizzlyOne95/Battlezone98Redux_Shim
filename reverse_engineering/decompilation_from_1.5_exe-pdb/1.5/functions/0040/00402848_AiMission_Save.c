/*
 * Entry: 00402848
 * Name: AiMission::Save
 * Namespace: AiMission
 * Signature: bool Save(AiMission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AiMission::Save(AiMission *this,_iobuf *param_1)

{
  list<AiProcess_*,std::allocator<AiProcess_*>_> *plVar1;
  bool bVar2;
  bool bVar3;
  AiProcess **ppAVar4;
  _Const_iterator<1> local_18;
  _Const_iterator<1> local_10;
  int local_8;
  
  bVar2 = ::out(param_1,"[AiMission]");
  if (missionSave == false) {
    local_8 = 0;
    plVar1 = &this->processes;
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_18,((this->processes)._Myhead)->_Next,plVar1);
    local_10._padding_ = local_18._padding_;
    local_10._Ptr = local_18._Ptr;
    if (bVar2) {
      while( true ) {
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_18,(this->processes)._Myhead,plVar1);
        bVar2 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                          (&local_10,&local_18);
        if (bVar2) break;
        ppAVar4 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                            (&local_10);
        if ((char)(*ppAVar4)->_padding_ == '\0') {
          local_8 = local_8 + 1;
        }
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++
                  (&local_10);
      }
    }
    bVar2 = ::out(param_1,&local_8,4,"size");
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_18,((this->processes)._Myhead)->_Next,plVar1);
    local_10._padding_ = local_18._padding_;
    local_10._Ptr = local_18._Ptr;
    if (bVar2) {
      do {
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  (&local_18,(this->processes)._Myhead,plVar1);
        bVar3 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                          (&local_10,&local_18);
        if (bVar3) break;
        ppAVar4 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                            (&local_10);
        if (*(bool *)&(*ppAVar4)->_padding_ == false) {
          bVar2 = RtimeClass::Save(param_1,(SObject *)*ppAVar4);
        }
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++
                  (&local_10);
      } while (bVar2 != false);
      if ((((bVar2 != false) && (bVar2 = ::out(param_1,&this->done,1,"done"), bVar2)) &&
          (bVar2 = ::out(param_1,&this->shutdownTime,4,"shutdownTime"), bVar2)) &&
         ((bVar2 = ::out(param_1,&this->failed,1,"failed"), bVar2 &&
          (bVar2 = ::out(param_1,this->resultName,0xe,"resultName"), bVar2)))) {
        return true;
      }
    }
    bVar2 = false;
  }
  return bVar2;
}
