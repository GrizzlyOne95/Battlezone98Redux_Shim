/*
 * Entry: 00550f5b
 * Name: PlayerNameList::Delete
 * Namespace: PlayerNameList
 * Signature: void Delete(PlayerNameList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::Delete(PlayerNameList *this,int param_1)

{
  int lParam;
  LRESULT LVar1;
  LRESULT LVar2;
  
  lParam = param_1;
  if ((-1 < param_1) && (param_1 < this->count)) {
    this->count = this->count + -1;
    free(this->name[param_1]);
    this->name[param_1] = this->name[this->count];
    free(this->email[param_1]);
    this->email[param_1] = this->email[this->count];
    free(this->url[param_1]);
    this->url[param_1] = this->url[this->count];
    free(this->description[param_1]);
    this->description[param_1] = this->description[this->count];
    free(this->flag[param_1]);
    this->flag[param_1] = this->flag[this->count];
    LVar1 = SendMessageA((HWND)this->hwnd,0x18b,0,0);
    if ((LVar1 != -1) && (param_1 = 0, 0 < LVar1)) {
      do {
        LVar2 = SendMessageA((HWND)this->hwnd,0x199,param_1,0);
        if (this->count == LVar2) {
          SendMessageA((HWND)this->hwnd,0x19a,param_1,lParam);
          return;
        }
        param_1 = param_1 + 1;
      } while (param_1 < LVar1);
    }
  }
  return;
}
