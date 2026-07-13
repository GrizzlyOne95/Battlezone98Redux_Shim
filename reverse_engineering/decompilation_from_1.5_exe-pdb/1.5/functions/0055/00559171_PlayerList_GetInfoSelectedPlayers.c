/*
 * Entry: 00559171
 * Name: PlayerList::GetInfoSelectedPlayers
 * Namespace: PlayerList
 * Signature: bool GetInfoSelectedPlayers(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PlayerList::GetInfoSelectedPlayers(PlayerList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  Player *pPVar2;
  char *pcVar3;
  int iVar4;
  PlayerInfo *pPVar5;
  PlayerList *local_8;
  
  local_8 = this;
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  this->l = wParam;
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x199,wParam,0);
    this->l = LVar1;
    pPVar2 = FindPlayer(this,(ushort)LVar1);
    if (pPVar2 != (Player *)0x0) {
      if (pPVar2->pinfo == (PlayerInfo *)0x0) {
        pcVar3 = malloc(0x40000);
        local_8 = (PlayerList *)0x40000;
        iVar4 = dpGetPlayerData(this->dp,pPVar2->id,0xe,pcVar3,&local_8,0);
        if (iVar4 != 0) {
          return false;
        }
        pPVar5 = operator_new(0x14);
        if (pPVar5 == (PlayerInfo *)0x0) {
          pPVar5 = (PlayerInfo *)0x0;
        }
        else {
          pPVar5 = PlayerInfo::PlayerInfo(pPVar5,pcVar3);
        }
        pPVar2->pinfo = pPVar5;
      }
      return true;
    }
  }
  return false;
}
