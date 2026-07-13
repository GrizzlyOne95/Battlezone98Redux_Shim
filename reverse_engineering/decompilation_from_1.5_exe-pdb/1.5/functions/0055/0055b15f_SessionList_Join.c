/*
 * Entry: 0055b15f
 * Name: SessionList::Join
 * Namespace: SessionList
 * Signature: dp_session_t * Join(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

dp_session_t * __thiscall SessionList::Join(SessionList *this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  WPARAM wParam;
  LRESULT LVar3;
  Session *pSVar4;
  int iVar5;
  char *unaff_ESI;
  char *unaff_EDI;
  undefined4 *puVar6;
  char *pcVar7;
  HWND__ *pHVar8;
  char *pcVar9;
  char local_118 [21];
  undefined1 local_103 [103];
  undefined1 local_9c [131];
  undefined4 uStack_19;
  undefined1 auStack_14 [6];
  undefined1 local_e;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_9c;
  if ((HWND)this->hList == (HWND)0x0) {
    return (dp_session_t *)0x0;
  }
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  if (wParam == 0xffffffff) {
    return (dp_session_t *)0x0;
  }
  LVar3 = SendMessageA((HWND)this->hList,0x199,wParam,0);
  this->l = LVar3;
  pSVar4 = FindSession(this,(short)LVar3);
  if (pSVar4 == (Session *)0x0) goto LAB_0055b347;
  iVar5 = 0;
  do {
    *(byte *)((int)&uStack_19 + iVar5 + 1) = (pSVar4->dp_session).szUserField[iVar5] & 0x7f;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 10);
  local_e = 0;
  puVar2 = &uStack_19;
  do {
    puVar6 = puVar2;
    puVar2 = (undefined4 *)((int)puVar6 + 1);
  } while (*(char *)((int)puVar6 + 1) != '\0');
  *(undefined4 *)((int)puVar6 + 1) = 0x6e7a622e;
  *(undefined1 *)((int)puVar6 + 5) = 0;
  iVar5 = ItemExists((char *)((int)&uStack_19 + 1));
  uVar1 = local_118._8_4_;
  if (iVar5 == 0) {
    pcVar9 = "Mission %s not found";
    pcVar7 = local_118;
    for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar9;
      pcVar9 = pcVar9 + 4;
      pcVar7 = pcVar7 + 4;
    }
    *pcVar7 = *pcVar9;
    memset(local_103,0,0xeb);
    read_text_label("multi_error","missing_map",local_118);
    do_error(this->hParentHwnd,local_118);
    goto LAB_0055b347;
  }
  if (((ushort)(pSVar4->dp_session).field7_0x15 & 4) == 0) {
    builtin_strncpy(local_118,"Game Locked",0xc);
    memset(local_118 + 0xc,0,0xf4);
    pcVar9 = "game_locked";
LAB_0055b2b8:
    read_text_label("multi_error",pcVar9,local_118);
    pHVar8 = this->hParentHwnd;
  }
  else {
    if ((pSVar4->dp_session).field5_0x11.maxPlayers <=
        (pSVar4->dp_session).field6_0x13.currentPlayers) {
      builtin_strncpy(local_118,"Game Full",10);
      local_118._10_2_ = SUB42(uVar1,2);
      memset(local_118 + 10,0,0xf6);
      pcVar9 = "game_full";
      goto LAB_0055b2b8;
    }
    if ((pSVar4->dp_session).szPassword[0] == '\0') {
      return &pSVar4->dp_session;
    }
    iVar5 = do_password(this->hParentHwnd);
    if (iVar5 == 0) goto LAB_0055b347;
    encrypt_password((pSVar4->dp_session).field8_0x17.sessionName,unaff_EDI,unaff_ESI);
    iVar5 = strncmp(do_password_password,(pSVar4->dp_session).szPassword,10);
    if (iVar5 == 0) {
      return &pSVar4->dp_session;
    }
    builtin_strncpy(local_118,"Incorrect password",0x13);
    memset(local_118 + 0x13,0,0xed);
    read_text_label("multi_error","incorrect_pass",local_118);
    pHVar8 = this->hParentHwnd;
  }
  do_error(pHVar8,local_118);
LAB_0055b347:
  LVar3 = SendMessageA((HWND)this->hList,0x186,0xffffffff,0);
  this->l = LVar3;
  return (dp_session_t *)0x0;
}
