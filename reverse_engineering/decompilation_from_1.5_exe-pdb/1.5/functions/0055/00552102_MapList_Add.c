/*
 * Entry: 00552102
 * Name: MapList::Add
 * Namespace: MapList
 * Signature: void Add(MapList * this, char * param_1, int param_2, int param_3, char * param_4, char param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
MapList::Add(MapList *this,char *param_1,int param_2,int param_3,char *param_4,char param_5)

{
  char cVar1;
  HWND__ *_Memory;
  HWND__ *pHVar2;
  char *pcVar3;
  void *pvVar4;
  WPARAM wParam;
  LRESULT LVar5;
  
  _Memory = this[1].hPlayerList;
  pHVar2 = realloc(_Memory,(int)((int)&this->s->name + 1) * 0x14);
  this[1].hPlayerList = pHVar2;
  if (pHVar2 == (HWND__ *)0x0) {
    this[1].hPlayerList = _Memory;
  }
  else {
    if (param_1 == (char *)0x0) {
      pcVar3 = (char *)0x1;
    }
    else {
      pcVar3 = param_1;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      pcVar3 = pcVar3 + (1 - (int)(param_1 + 1));
    }
    pvVar4 = malloc((size_t)pcVar3);
    this[1].hPlayerList[(int)this->s * 5].unused = (int)pvVar4;
    pcVar3 = (char *)this[1].hPlayerList[(int)this->s * 5].unused;
    if (pcVar3 != (char *)0x0) {
      if (param_1 == (char *)0x0) {
        *pcVar3 = '\0';
      }
      else {
        do {
          cVar1 = *param_1;
          param_1 = param_1 + 1;
          *pcVar3 = cVar1;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
      }
      if (param_2 < 2) {
        param_2 = 2;
      }
      if (0xf < param_2) {
        param_2 = 0xf;
      }
      if (param_3 < 2) {
        param_3 = 2;
      }
      if (0xf < param_3) {
        param_3 = 0xf;
      }
      if (param_3 < param_2) {
        param_2 = param_3;
      }
      this[1].hPlayerList[(int)this->s * 5 + 1].unused = param_2;
      this[1].hPlayerList[(int)this->s * 5 + 2].unused = param_3;
      if (param_4 == (char *)0x0) {
        pcVar3 = (char *)0x1;
      }
      else {
        pcVar3 = param_4;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = pcVar3 + (1 - (int)(param_4 + 1));
      }
      pvVar4 = malloc((size_t)pcVar3);
      this[1].hPlayerList[(int)this->s * 5 + 3].unused = (int)pvVar4;
      pcVar3 = (char *)(this[1].hPlayerList + (int)this->s * 5)[3].unused;
      if (pcVar3 == (char *)0x0) {
        free((void *)this[1].hPlayerList[(int)this->s * 5].unused);
      }
      else {
        if (param_4 == (char *)0x0) {
          *pcVar3 = '\0';
        }
        else {
          do {
            cVar1 = *param_4;
            param_4 = param_4 + 1;
            *pcVar3 = cVar1;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
        }
        *(char *)&this[1].hPlayerList[(int)this->s * 5 + 4].unused = param_5;
        wParam = SendMessageA((HWND)this->hwnd,0x180,0,
                              this[1].hPlayerList[(int)this->s * 5 + 3].unused);
        if ((wParam != 0xffffffff) && (wParam != 0xfffffffe)) {
          LVar5 = SendMessageA((HWND)this->hwnd,0x19a,wParam,(LPARAM)this->s);
          if (LVar5 != -1) {
            this->s = (_s *)((int)&this->s->name + 1);
            return;
          }
          SendMessageA((HWND)this->hwnd,0x182,wParam,0);
        }
        free((void *)this[1].hPlayerList[(int)this->s * 5].unused);
        free((void *)this[1].hPlayerList[(int)this->s * 5 + 3].unused);
      }
    }
  }
  return;
}
