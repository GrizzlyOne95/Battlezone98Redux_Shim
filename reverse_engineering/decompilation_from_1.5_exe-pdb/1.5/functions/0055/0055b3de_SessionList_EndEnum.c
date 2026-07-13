/*
 * Entry: 0055b3de
 * Name: SessionList::EndEnum
 * Namespace: SessionList
 * Signature: void EndEnum(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SessionList::EndEnum(SessionList *this)

{
  vector<Session_*,std::allocator<Session_*>_> *this_00;
  short sVar1;
  Session *pSVar2;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> _Var3;
  bool bVar4;
  Session **ppSVar5;
  LRESULT LVar6;
  LRESULT LVar7;
  int iVar8;
  Chat *this_01;
  char *pcVar9;
  char *pcVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_11c;
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_> local_114;
  char local_109;
  char local_108 [44];
  undefined1 local_dc [64];
  undefined1 local_9c [148];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_9c;
  this_00 = &this->sessionV;
  std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            (&local_11c,(this->sessionV)._Myfirst,(_Container_base_aux *)this_00);
  local_114._padding_ = local_11c._padding_;
  ppSVar5 = (this->sessionV)._Mylast;
  uVar11 = SUB42(ppSVar5,0);
  uVar12 = (undefined2)((uint)ppSVar5 >> 0x10);
  local_114._Myptr = local_11c._Myptr;
  while( true ) {
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
    _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
              (&local_11c,(Session **)CONCAT22(uVar12,uVar11),(_Container_base_aux *)this_00);
    bVar4 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator==
                      (&local_114,&local_11c);
    if (bVar4) break;
    ppSVar5 = std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator*
                        (&local_114);
    pSVar2 = *ppSVar5;
    if (pSVar2->mark < 0) {
      DeleteListItem(this,(pSVar2->dp_session).field4_0xf.karma);
      operator_delete(pSVar2);
      _Var3._Myptr._0_2_ = (short)local_114._padding_;
      _Var3._padding_ = (int)&local_11c;
      _Var3._Myptr._2_2_ = (short)((uint)local_114._padding_ >> 0x10);
      std::vector<Session_*,std::allocator<Session_*>_>::erase(this_00,_Var3);
      break;
    }
    std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++(&local_114);
    ppSVar5 = (this->sessionV)._Mylast;
    uVar11 = SUB42(ppSVar5,0);
    uVar12 = (undefined2)((uint)ppSVar5 >> 0x10);
  }
  if (chat_state == 0) {
    iVar8 = this->countWait;
    if (iVar8 < 1) {
      if (this->bWaitSes != false) {
        this->bWaitSes = false;
      }
      sVar1 = this->dp_karma_found;
      if (sVar1 == 0) {
        if (iVar8 == 0) {
          createRoom = true;
        }
      }
      else if (sVar1 != this->dp_karma_selected) {
        FindSession(this,sVar1);
        LVar6 = SendMessageA((HWND)this->hList,0x18b,0,0);
        this->l = LVar6;
        if (LVar6 == -1) {
          return;
        }
        local_114._Myptr = (Session **)0x0;
        if (0 < LVar6) {
          do {
            LVar7 = SendMessageA((HWND)this->hList,0x199,(WPARAM)local_114._Myptr,0);
            this->l = LVar7;
            if (LVar7 == this->dp_karma_found) {
              local_109 = '\0';
              LVar6 = SendMessageA((HWND)this->hList,0x186,(WPARAM)local_114._Myptr,0);
              this->l = LVar6;
              if (this->dp_karma_selected != 0) {
                local_109 = '\x01';
              }
              SelectionChanged(this);
              if ((this->dp_karma_selected != 0) && (local_109 != '\0')) {
                pcVar9 = "<system> merging with the best lobby found ";
                pcVar10 = local_108;
                for (iVar8 = 0xb; iVar8 != 0; iVar8 = iVar8 + -1) {
                  *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar10 = pcVar10 + 4;
                }
                memset(local_dc,0,0xd4);
                read_text_label("multi_message","system_best",local_108);
                Chat::Append(this_01,(char *)&chatRoom);
              }
              break;
            }
            local_114._Myptr = (Session **)((int)local_114._Myptr + 1);
          } while ((int)local_114._Myptr < LVar6);
        }
      }
      if (this->countWait == 0) {
        this->countWait = -1;
      }
    }
    else if ((this->bWaitSes == false) || (this->bFoundSes != false)) {
      this->countWait = iVar8 + -1;
    }
  }
  return;
}
