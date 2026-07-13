/*
 * Entry: 00552647
 * Name: PhoneNumberList::Add
 * Namespace: PhoneNumberList
 * Signature: void Add(PhoneNumberList * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PhoneNumberList::Add(PhoneNumberList *this,char *param_1,char *param_2)

{
  char cVar1;
  char **ppcVar2;
  char **ppcVar3;
  char **ppcVar4;
  char *pcVar5;
  WPARAM wParam;
  LRESULT LVar6;
  char local_d0 [92];
  undefined1 local_74 [108];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_74;
  ppcVar4 = this->name;
  ppcVar2 = this->number;
  ppcVar3 = realloc(ppcVar4,this->count * 4 + 4);
  this->name = ppcVar3;
  if (ppcVar3 == (char **)0x0) {
    this->name = ppcVar4;
  }
  else {
    ppcVar4 = realloc(this->number,this->count * 4 + 4);
    this->number = ppcVar4;
    if (ppcVar4 == (char **)0x0) {
      this->number = ppcVar2;
    }
    else {
      if (param_1 == (char *)0x0) {
        pcVar5 = (char *)0x1;
      }
      else {
        pcVar5 = param_1;
        do {
          cVar1 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar1 != '\0');
        pcVar5 = pcVar5 + (1 - (int)(param_1 + 1));
      }
      pcVar5 = malloc((size_t)pcVar5);
      this->name[this->count] = pcVar5;
      if (this->name[this->count] != (char *)0x0) {
        pcVar5 = this->name[this->count];
        if (param_1 == (char *)0x0) {
          *pcVar5 = '\0';
        }
        else {
          do {
            cVar1 = *param_1;
            param_1 = param_1 + 1;
            *pcVar5 = cVar1;
            pcVar5 = pcVar5 + 1;
          } while (cVar1 != '\0');
        }
        if (param_2 == (char *)0x0) {
          pcVar5 = (char *)0x1;
        }
        else {
          pcVar5 = param_2;
          do {
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar1 != '\0');
          pcVar5 = pcVar5 + (1 - (int)(param_2 + 1));
        }
        pcVar5 = malloc((size_t)pcVar5);
        this->number[this->count] = pcVar5;
        if (this->number[this->count] == (char *)0x0) {
          free(this->name[this->count]);
        }
        else {
          pcVar5 = this->number[this->count];
          if (param_2 == (char *)0x0) {
            *pcVar5 = '\0';
          }
          else {
            do {
              cVar1 = *param_2;
              param_2 = param_2 + 1;
              *pcVar5 = cVar1;
              pcVar5 = pcVar5 + 1;
            } while (cVar1 != '\0');
          }
          sprintf(local_d0,"%s   %s",this->name[this->count],this->number[this->count]);
          wParam = SendMessageA((HWND)this->hwnd,0x180,0,(LPARAM)local_d0);
          if ((wParam != 0xffffffff) && (wParam != 0xfffffffe)) {
            LVar6 = SendMessageA((HWND)this->hwnd,0x19a,wParam,this->count);
            if (LVar6 != -1) {
              SendMessageA((HWND)this->hwnd,0x186,wParam,0);
              this->count = this->count + 1;
              InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
              return;
            }
            SendMessageA((HWND)this->hwnd,0x182,wParam,0);
          }
          free(this->name[this->count]);
          free(this->number[this->count]);
        }
      }
    }
  }
  return;
}
