/*
 * Entry: 00558fd8
 * Name: PlayerList::SendMessageToSelectedPlayers
 * Namespace: PlayerList
 * Signature: bool SendMessageToSelectedPlayers(PlayerList * this, HWND__ * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __thiscall
PlayerList::SendMessageToSelectedPlayers(PlayerList *this,HWND__ *param_1,ushort param_2)

{
  WPARAM wParam;
  LRESULT LVar1;
  Player *pPVar2;
  char *unaff_EDI;
  undefined2 in_stack_0000000a;
  CHAR local_fc [128];
  undefined1 local_7c [115];
  undefined1 local_9;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  this->l = wParam;
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x199,wParam,0);
    this->l = LVar1;
    GetWindowTextA((HWND)param_1,local_fc,0xf4);
    SetWindowTextA((HWND)param_1,"");
    local_9 = 0;
    send_private_message(_param_2,(ushort)this->l,(ushort)local_fc,unaff_EDI);
    pPVar2 = FindPlayer(this,(ushort)this->l);
    Chat::AppendWhisperSent(this->chat,pPVar2->caName,local_fc);
  }
  return wParam != 0xffffffff;
}
