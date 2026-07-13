/*
 * Entry: 00555f01
 * Name: FlagList::SelectionDown
 * Namespace: FlagList
 * Signature: void SelectionDown(FlagList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagList::SelectionDown(FlagList *this)

{
  int *piVar1;
  char cVar2;
  ShellBitmap *pSVar3;
  char *pcVar4;
  char *pcVar5;
  
  piVar1 = &this->currentSelection;
  *piVar1 = *piVar1 + -1;
  if (*piVar1 < 0) {
    this->currentSelection = this->count + -1;
  }
  if (this->currentSelection < 0) {
    this->currentSelection = 0;
  }
  pSVar3 = this->shellBitmap;
  if (pSVar3 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar3);
    operator_delete(pSVar3);
  }
  if (this->count != 0) {
    pSVar3 = operator_new(0x20);
    if (pSVar3 == (ShellBitmap *)0x0) {
      pSVar3 = (ShellBitmap *)0x0;
    }
    else {
      pSVar3 = ShellBitmap::ShellBitmap
                         (pSVar3,this->s[this->currentSelection].filename,this->xPos,this->yPos);
    }
    this->shellBitmap = pSVar3;
    InvalidateRect((HWND)this->h,(RECT *)&this->rect,0);
    pcVar4 = this->s[this->currentSelection].filename;
    pcVar5 = Net::pcFlagName;
    do {
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      *pcVar5 = cVar2;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
  }
  return;
}
