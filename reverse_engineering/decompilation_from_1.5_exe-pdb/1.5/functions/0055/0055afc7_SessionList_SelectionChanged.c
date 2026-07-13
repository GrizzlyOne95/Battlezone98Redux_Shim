/*
 * Entry: 0055afc7
 * Name: SessionList::SelectionChanged
 * Namespace: SessionList
 * Signature: void SelectionChanged(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SessionList::SelectionChanged(SessionList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  Session *pSVar2;
  int iVar3;
  char *unaff_ESI;
  char *unaff_EDI;
  char local_108 [124];
  undefined1 local_8c [132];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_8c;
  if ((HWND)this->hList == (HWND)0x0) {
    return;
  }
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  if (wParam == 0xffffffff) {
    return;
  }
  LVar1 = SendMessageA((HWND)this->hList,0x199,wParam,0);
  this->l = LVar1;
  if (LVar1 == this->dp_karma_selected) {
    return;
  }
  pSVar2 = FindSession(this,(short)LVar1);
  if (pSVar2 == (Session *)0x0) {
    return;
  }
  if ((pSVar2->dp_session).szPassword[0] == '\0') {
LAB_0055b0ea:
    this->dp_karma_selected = (short)this->l;
    chat_state = 5;
    Net::Close();
    if ((this->dp != (dp_s *)0x0) &&
       (dp_result = dpOpen(this->dp,pSVar2,dpJoinRoomOpenCallback,0), dp_result != 0)) {
      this->dp_karma_selected = 0;
      SendMessageA((HWND)this->hList,0x186,0xffffffff,0);
      JoinLobby(this);
    }
    Chat::Clear((Chat *)&chatRoom);
  }
  else {
    iVar3 = do_password(this->hParentHwnd);
    if (iVar3 == 0) {
      LVar1 = SendMessageA((HWND)this->hList,0x186,0xffffffff,0);
    }
    else {
      encrypt_password((pSVar2->dp_session).field8_0x17.sessionName,unaff_ESI,unaff_EDI);
      iVar3 = strncmp(do_password_password,(pSVar2->dp_session).szPassword,10);
      if (iVar3 == 0) goto LAB_0055b0ea;
      builtin_strncpy(local_108,"Incorrect password",0x13);
      memset(local_108 + 0x13,0,0xed);
      read_text_label("multi_error","incorrect_pass",local_108);
      do_error(this->hParentHwnd,local_108);
      LVar1 = SendMessageA((HWND)this->hList,0x186,0xffffffff,0);
    }
    this->l = LVar1;
  }
  return;
}
