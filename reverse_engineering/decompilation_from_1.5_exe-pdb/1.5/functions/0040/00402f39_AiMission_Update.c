/*
 * Entry: 00402f39
 * Name: AiMission::Update
 * Namespace: AiMission
 * Signature: void Update(AiMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AiMission::Update(AiMission *this)

{
  char cVar1;
  GameObject *pGVar2;
  AiProcess *pAVar3;
  bool bVar4;
  char *pcVar5;
  AiProcess **ppAVar6;
  int iVar7;
  float unaff_EDI;
  float fVar8;
  _Node *p_Var9;
  list<AiProcess_*,std::allocator<AiProcess_*>_> local_34;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_18;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_10;
  GameObject *local_8;
  
  if (((this->done == false) || (fVar8 = Get_Time(), fVar8 <= this->shutdownTime)) ||
     (bVar4 = AudioDone(), !bVar4)) {
    AISchedule_Simulate();
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::
    list<AiProcess_*,std::allocator<AiProcess_*>_>(&local_34);
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              ((_Const_iterator<1> *)&local_18,((this->processes)._Myhead)->_Next,&this->processes);
    local_10._padding_ = local_18._padding_;
    p_Var9 = (this->processes)._Myhead;
    local_10._Myptr = local_18._Myptr;
    while( true ) {
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                ((_Const_iterator<1> *)&local_18,p_Var9,&this->processes);
      bVar4 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                        ((_Const_iterator<1> *)&local_10,(_Const_iterator<1> *)&local_18);
      if (bVar4) break;
      ppAVar6 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                          ((_Const_iterator<1> *)&local_10);
      pGVar2 = (GameObject *)*ppAVar6;
      local_8 = pGVar2;
      if ((pGVar2->_padding_ != 0) ||
         ((**(code **)(pGVar2->_padding_ + 0x1c))(), pGVar2->_padding_ != 0)) {
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::push_back
                  (&local_34,(AiProcess **)&local_8);
      }
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++
                ((_Const_iterator<1> *)&local_10);
      p_Var9 = (this->processes)._Myhead;
    }
    while (local_34._Mysize != 0) {
      ppAVar6 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::back(&local_34);
      pAVar3 = *ppAVar6;
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::pop_back(&local_34);
      if (pAVar3 != (AiProcess *)0x0) {
        (**(code **)pAVar3->_padding_)(1);
      }
    }
    local_8 = (GameObject *)TimeStep();
    iVar7 = Net_IsNetGame();
    if (iVar7 == 0) {
      if (GameObject::userObject != (GameObject *)0x0) {
        CheckBoundary(local_8,unaff_EDI);
      }
    }
    else {
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&local_10,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
      while( true ) {
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
        _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                  (&local_18,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
        bVar4 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                          (&local_10,&local_18);
        if (bVar4) break;
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_10);
        CheckBoundary(local_8,unaff_EDI);
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_10);
      }
    }
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Tidy(&local_34);
    operator_delete((void *)local_34._padding_);
  }
  else {
    SetRunning((uint)(this->failed == false));
    pcVar5 = this->resultName;
    if (*pcVar5 == '\0') {
      builtin_strncpy(cMissionResult,"nofile",7);
    }
    else {
      iVar7 = (int)cMissionResult - (int)pcVar5;
      do {
        cVar1 = *pcVar5;
        pcVar5[iVar7] = cVar1;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
    }
  }
  return;
}
