/*
 * Entry: 00550ead
 * Name: PlayerNameList::Init
 * Namespace: PlayerNameList
 * Signature: void Init(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::Init(PlayerNameList *this)

{
  int iVar1;
  
  iVar1 = 0;
  if ((HWND)this->hwnd != (HWND)0x0) {
    SendMessageA((HWND)this->hwnd,0x184,0,0);
  }
  if (this->count != 0) {
    if (0 < this->count) {
      do {
        free(this->name[iVar1]);
        free(this->email[iVar1]);
        free(this->url[iVar1]);
        free(this->description[iVar1]);
        free(this->flag[iVar1]);
        iVar1 = iVar1 + 1;
      } while (iVar1 < this->count);
    }
    free(this->name);
    free(this->email);
    free(this->url);
    free(this->description);
    free(this->flag);
    this->name = (char **)0x0;
    this->email = (char **)0x0;
    this->url = (char **)0x0;
    this->description = (char **)0x0;
    this->flag = (char **)0x0;
  }
  this->count = 0;
  if ((HWND)this->hwnd != (HWND)0x0) {
    InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  }
  return;
}
