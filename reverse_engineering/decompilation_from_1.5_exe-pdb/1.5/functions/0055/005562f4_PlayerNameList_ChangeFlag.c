/*
 * Entry: 005562f4
 * Name: PlayerNameList::ChangeFlag
 * Namespace: PlayerNameList
 * Signature: void ChangeFlag(PlayerNameList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::ChangeFlag(PlayerNameList *this,char *param_1)

{
  char cVar1;
  WPARAM wParam;
  LRESULT LVar2;
  char *pcVar3;
  
  if ((param_1 != (char *)0x0) &&
     (wParam = SendMessageA((HWND)this->hwnd,0x188,0,0), wParam != 0xffffffff)) {
    LVar2 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if ((LVar2 != -1) && ((-1 < LVar2 && (LVar2 < this->count)))) {
      pcVar3 = param_1;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      pcVar3 = realloc(this->flag[LVar2],(size_t)(pcVar3 + (1 - (int)(param_1 + 1))));
      this->flag[LVar2] = pcVar3;
      pcVar3 = this->flag[LVar2];
      do {
        cVar1 = *param_1;
        param_1 = param_1 + 1;
        *pcVar3 = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
    }
    Save(this,"netnam2.txt");
  }
  return;
}
