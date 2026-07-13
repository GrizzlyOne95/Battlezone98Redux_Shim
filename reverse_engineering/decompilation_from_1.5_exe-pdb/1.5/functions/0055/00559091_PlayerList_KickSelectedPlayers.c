/*
 * Entry: 00559091
 * Name: PlayerList::KickSelectedPlayers
 * Namespace: PlayerList
 * Signature: void KickSelectedPlayers(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PlayerList::KickSelectedPlayers(PlayerList *this)

{
  char cVar1;
  WPARAM wParam;
  LRESULT LVar2;
  Player *pPVar3;
  Chat *this_00;
  char local_108 [124];
  undefined1 local_8c [132];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_8c;
  cVar1 = (**(code **)(this->_padding_ + 0x14))(Net::myPlayerID);
  if (cVar1 != '\0') {
    wParam = SendMessageA((HWND)this->hList,0x188,0,0);
    this->l = wParam;
    if (wParam != 0xffffffff) {
      LVar2 = SendMessageA((HWND)this->hList,0x199,wParam,0);
      this->l = LVar2;
      pPVar3 = FindPlayer(this,(ushort)LVar2);
      if (pPVar3->id != Net::myPlayerID) {
        builtin_strncpy(local_108,"Kicked %s",10);
        memset(local_108 + 10,0,0xf6);
        read_text_label("multi_message","kicked",local_108);
        Chat::Append(this_00,(char *)this->chat);
        Net_KickPlayer((ushort)this->l);
      }
    }
  }
  return;
}
