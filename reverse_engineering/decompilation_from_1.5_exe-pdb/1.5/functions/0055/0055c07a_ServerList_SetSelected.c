/*
 * Entry: 0055c07a
 * Name: ServerList::SetSelected
 * Namespace: ServerList
 * Signature: int SetSelected(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __thiscall ServerList::SetSelected(ServerList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  char local_108 [25];
  undefined1 local_ef [103];
  undefined1 local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_88;
  `public:_int___thiscall_ServerList::SetSelected(void)'::__l2::buffer._0_1_ = 0;
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  this->l = wParam;
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x189,wParam,0xc70038);
    this->l = LVar1;
    if ((LVar1 != -1) &&
       (pcVar2 = strchr((char *)&`public:_int___thiscall_ServerList::SetSelected(void)'::__l2::
                                 buffer,0x20), pcVar2 != (char *)0x0)) {
      *pcVar2 = '\0';
      dpEnumServers(this->dp,0,0,0);
      EndEnum(this);
      iVar3 = dpSetGameServerEx(this->dp,&`public:_int___thiscall_ServerList::SetSelected(void)'::
                                          __l2::buffer,Net::session_type);
      if (iVar3 == 0) {
        iVar3 = 0;
        do {
          pcVar2 = (char *)((int)&`public:_int___thiscall_ServerList::SetSelected(void)'::__l2::
                                  buffer + iVar3);
          Net::hostname[iVar3] = *pcVar2;
          iVar3 = iVar3 + 1;
        } while (*pcVar2 != '\0');
        return 1;
      }
      pcVar2 = "Cannot connect to server";
      pcVar4 = local_108;
      for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
        *(undefined4 *)pcVar4 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar4 = pcVar4 + 4;
      }
      *pcVar4 = *pcVar2;
      memset(local_ef,0,0xe7);
      read_text_label("multi_error","cannot_connect_server",local_108);
      do_error(this->hParent,local_108);
    }
  }
  return 0;
}
