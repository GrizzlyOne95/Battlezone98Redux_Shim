/*
 * Entry: 00403edb
 * Name: EmptyMission::Update
 * Namespace: EmptyMission
 * Signature: void Update(EmptyMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EmptyMission::Update(EmptyMission *this)

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
  list<AiProcess_*,std::allocator<AiProcess_*>_> lStack_34;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_18;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> _Stack_10;
  GameObject *pGStack_8;
  
  if (((this->field_0x24 == '\0') || (fVar8 = Get_Time(), fVar8 <= *(float *)&this->field_0x28)) ||
     (bVar4 = AudioDone(), !bVar4)) {
    AISchedule_Simulate();
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::
    list<AiProcess_*,std::allocator<AiProcess_*>_>(&lStack_34);
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
              ((_Const_iterator<1> *)&_Stack_18,(_Node *)**(undefined4 **)&this->field_0x1c,
               (list<AiProcess_*,std::allocator<AiProcess_*>_> *)&this->field_0x8);
    _Stack_10._padding_ = _Stack_18._padding_;
    p_Var9 = *(_Node **)&this->field_0x1c;
    _Stack_10._Myptr = _Stack_18._Myptr;
    while( true ) {
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::_Const_iterator<1>
                ((_Const_iterator<1> *)&_Stack_18,p_Var9,
                 (list<AiProcess_*,std::allocator<AiProcess_*>_> *)&this->field_0x8);
      bVar4 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator==
                        ((_Const_iterator<1> *)&_Stack_10,(_Const_iterator<1> *)&_Stack_18);
      if (bVar4) break;
      ppAVar6 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator*
                          ((_Const_iterator<1> *)&_Stack_10);
      pGVar2 = (GameObject *)*ppAVar6;
      pGStack_8 = pGVar2;
      if ((pGVar2->_padding_ != 0) ||
         ((**(code **)(pGVar2->_padding_ + 0x1c))(), pGVar2->_padding_ != 0)) {
        std::list<AiProcess_*,std::allocator<AiProcess_*>_>::push_back
                  (&lStack_34,(AiProcess **)&pGStack_8);
      }
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Const_iterator<1>::operator++
                ((_Const_iterator<1> *)&_Stack_10);
      p_Var9 = *(_Node **)&this->field_0x1c;
    }
    while (lStack_34._Mysize != 0) {
      ppAVar6 = std::list<AiProcess_*,std::allocator<AiProcess_*>_>::back(&lStack_34);
      pAVar3 = *ppAVar6;
      std::list<AiProcess_*,std::allocator<AiProcess_*>_>::pop_back(&lStack_34);
      if (pAVar3 != (AiProcess *)0x0) {
        (**(code **)pAVar3->_padding_)(1);
      }
    }
    pGStack_8 = (GameObject *)TimeStep();
    iVar7 = Net_IsNetGame();
    if (iVar7 == 0) {
      if (GameObject::userObject != (GameObject *)0x0) {
        CheckBoundary(pGStack_8,unaff_EDI);
      }
    }
    else {
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&_Stack_10,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
      while( true ) {
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
        _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                  (&_Stack_18,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
        bVar4 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                          (&_Stack_10,&_Stack_18);
        if (bVar4) break;
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&_Stack_10);
        CheckBoundary(pGStack_8,unaff_EDI);
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&_Stack_10);
      }
    }
    std::list<AiProcess_*,std::allocator<AiProcess_*>_>::_Tidy(&lStack_34);
    operator_delete((void *)lStack_34._padding_);
  }
  else {
    SetRunning((uint)(this->field_0x2c == '\0'));
    pcVar5 = &this->field_0x2d;
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
