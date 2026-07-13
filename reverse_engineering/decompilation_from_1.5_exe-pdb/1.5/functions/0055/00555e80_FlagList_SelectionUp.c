/*
 * Entry: 00555e80
 * Name: FlagList::SelectionUp
 * Namespace: FlagList
 * Signature: void SelectionUp(FlagList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagList::SelectionUp(FlagList *this)

{
  char cVar1;
  ShellBitmap *pSVar2;
  char *pcVar3;
  char *pcVar4;
  
  this->currentSelection = this->currentSelection + 1;
  if (this->count <= this->currentSelection) {
    this->currentSelection = 0;
  }
  pSVar2 = this->shellBitmap;
  if (pSVar2 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar2);
    operator_delete(pSVar2);
  }
  if (this->count != 0) {
    pSVar2 = operator_new(0x20);
    if (pSVar2 == (ShellBitmap *)0x0) {
      pSVar2 = (ShellBitmap *)0x0;
    }
    else {
      pSVar2 = ShellBitmap::ShellBitmap
                         (pSVar2,this->s[this->currentSelection].filename,this->xPos,this->yPos);
    }
    this->shellBitmap = pSVar2;
    InvalidateRect((HWND)this->h,(RECT *)&this->rect,0);
    pcVar3 = this->s[this->currentSelection].filename;
    pcVar4 = Net::pcFlagName;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  return;
}
