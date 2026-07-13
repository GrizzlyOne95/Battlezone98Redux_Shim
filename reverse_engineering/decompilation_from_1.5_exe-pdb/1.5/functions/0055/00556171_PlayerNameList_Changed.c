/*
 * Entry: 00556171
 * Name: PlayerNameList::Changed
 * Namespace: PlayerNameList
 * Signature: void Changed(PlayerNameList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PlayerNameList::Changed(PlayerNameList *this,int param_1)

{
  char cVar1;
  WPARAM wParam;
  LRESULT LVar2;
  char *pcVar3;
  char *pcVar4;
  CHAR local_1d0 [256];
  CHAR local_d0 [88];
  undefined1 local_78 [12];
  CHAR local_6c [100];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if (wParam != 0xffffffff) {
    LVar2 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if (((LVar2 != -1) && (-1 < LVar2)) && (LVar2 < this->count)) {
      if (param_1 == 0) {
        GetWindowTextA((HWND)this->hwndMail,local_6c,100);
        pcVar3 = local_6c;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = realloc(this->email[LVar2],(size_t)(pcVar3 + (1 - (int)(local_6c + 1))));
        this->email[LVar2] = pcVar3;
        pcVar4 = this->email[LVar2];
        pcVar3 = local_6c;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
      }
      else if (param_1 == 1) {
        GetWindowTextA((HWND)this->hwndURL,local_d0,100);
        pcVar3 = local_d0;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = realloc(this->url[LVar2],(size_t)(pcVar3 + (1 - (int)(local_d0 + 1))));
        this->url[LVar2] = pcVar3;
        pcVar4 = this->url[LVar2];
        pcVar3 = local_d0;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
      }
      else if (param_1 == 2) {
        GetWindowTextA((HWND)this->hwndDescription,local_1d0,0xfd);
        pcVar3 = local_1d0;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = realloc(this->description[LVar2],(size_t)(pcVar3 + (1 - (int)(local_1d0 + 1))));
        this->description[LVar2] = pcVar3;
        pcVar4 = this->description[LVar2];
        pcVar3 = local_1d0;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
          *pcVar4 = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
      }
    }
    Save(this,"netnam2.txt");
  }
  return;
}
