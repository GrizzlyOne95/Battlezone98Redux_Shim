/*
 * Entry: 005598ef
 * Name: MapList::SelectionChanged
 * Namespace: MapList
 * Signature: void SelectionChanged(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::SelectionChanged(MapList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  char *pcVar2;
  
  this->count = -1;
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if ((((LVar1 != -1) && (-1 < LVar1)) && (LVar1 < (int)this->s)) &&
       (this->mapDesc != (TextWindow *)0x0)) {
      this->count = LVar1;
      OptionBox::SetCurrentValue(this->playerLimit,this[1].hPlayerList[LVar1 * 5 + 2].unused);
      SetSessionDescName(Net::dp,(char *)this[1].hPlayerList[LVar1 * 5].unused);
      SetSessionDescMaxPlayers(Net::dp,this[1].hPlayerList[LVar1 * 5 + 2].unused);
      pcVar2 = GetSessionDescName(Net::dp);
      Update(this,pcVar2);
      if (syncBox != (OptionBox *)0x0) {
        SyncGamePlayerList::Reset(&playersInSyncGame);
        UpdateWindow((HWND)this->hPlayerList);
      }
      SetSessionDescCommSat(Net::dp,Net::bCommSat);
      SetSessionDescBarracks(Net::dp,Net::bBarracks);
      SetSessionDescSplint(Net::dp,Net::bSplint);
    }
  }
  if (this->count < 0) {
    Update(this,"");
  }
  return;
}
