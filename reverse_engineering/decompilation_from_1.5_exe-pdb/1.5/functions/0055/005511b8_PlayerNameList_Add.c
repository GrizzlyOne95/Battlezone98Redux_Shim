/*
 * Entry: 005511b8
 * Name: PlayerNameList::Add
 * Namespace: PlayerNameList
 * Signature: void Add(PlayerNameList * this, char * param_1, char * param_2, char * param_3, char * param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PlayerNameList::Add(PlayerNameList *this,char *param_1,char *param_2,char *param_3,char *param_4,
                   char *param_5)

{
  char cVar1;
  char **ppcVar2;
  char **ppcVar3;
  char **ppcVar4;
  char **ppcVar5;
  char **ppcVar6;
  char **ppcVar7;
  char *pcVar8;
  WPARAM wParam;
  LRESULT LVar9;
  
  ppcVar7 = this->email;
  ppcVar6 = this->name;
  ppcVar2 = this->url;
  ppcVar3 = this->description;
  ppcVar4 = this->flag;
  ppcVar5 = realloc(ppcVar6,this->count * 4 + 4);
  this->name = ppcVar5;
  if (ppcVar5 == (char **)0x0) {
    this->name = ppcVar6;
  }
  else {
    ppcVar6 = realloc(this->email,this->count * 4 + 4);
    this->email = ppcVar6;
    if (ppcVar6 == (char **)0x0) {
      this->email = ppcVar7;
    }
    else {
      ppcVar7 = realloc(this->url,this->count * 4 + 4);
      this->url = ppcVar7;
      if (ppcVar7 == (char **)0x0) {
        this->url = ppcVar2;
      }
      else {
        ppcVar7 = realloc(this->description,this->count * 4 + 4);
        this->description = ppcVar7;
        if (ppcVar7 == (char **)0x0) {
          this->description = ppcVar3;
        }
        else {
          ppcVar7 = realloc(this->flag,this->count * 4 + 4);
          this->flag = ppcVar7;
          if (ppcVar7 == (char **)0x0) {
            this->flag = ppcVar4;
          }
          else {
            if (param_1 == (char *)0x0) {
              pcVar8 = (char *)0x1;
            }
            else {
              pcVar8 = param_1;
              do {
                cVar1 = *pcVar8;
                pcVar8 = pcVar8 + 1;
              } while (cVar1 != '\0');
              pcVar8 = pcVar8 + (1 - (int)(param_1 + 1));
            }
            pcVar8 = malloc((size_t)pcVar8);
            this->name[this->count] = pcVar8;
            if (this->name[this->count] != (char *)0x0) {
              pcVar8 = this->name[this->count];
              if (param_1 == (char *)0x0) {
                *pcVar8 = '\0';
              }
              else {
                do {
                  cVar1 = *param_1;
                  param_1 = param_1 + 1;
                  *pcVar8 = cVar1;
                  pcVar8 = pcVar8 + 1;
                } while (cVar1 != '\0');
              }
              if (param_2 == (char *)0x0) {
                pcVar8 = (char *)0x1;
              }
              else {
                pcVar8 = param_2;
                do {
                  cVar1 = *pcVar8;
                  pcVar8 = pcVar8 + 1;
                } while (cVar1 != '\0');
                pcVar8 = pcVar8 + (1 - (int)(param_2 + 1));
              }
              pcVar8 = malloc((size_t)pcVar8);
              this->email[this->count] = pcVar8;
              if (this->email[this->count] == (char *)0x0) {
                free(this->name[this->count]);
              }
              else {
                pcVar8 = this->email[this->count];
                if (param_2 == (char *)0x0) {
                  *pcVar8 = '\0';
                }
                else {
                  do {
                    cVar1 = *param_2;
                    param_2 = param_2 + 1;
                    *pcVar8 = cVar1;
                    pcVar8 = pcVar8 + 1;
                  } while (cVar1 != '\0');
                }
                if (param_3 == (char *)0x0) {
                  pcVar8 = (char *)0x1;
                }
                else {
                  pcVar8 = param_3;
                  do {
                    cVar1 = *pcVar8;
                    pcVar8 = pcVar8 + 1;
                  } while (cVar1 != '\0');
                  pcVar8 = pcVar8 + (1 - (int)(param_3 + 1));
                }
                pcVar8 = malloc((size_t)pcVar8);
                this->url[this->count] = pcVar8;
                if (this->url[this->count] == (char *)0x0) {
                  free(this->email[this->count]);
                  free(this->name[this->count]);
                }
                else {
                  pcVar8 = this->url[this->count];
                  if (param_3 == (char *)0x0) {
                    *pcVar8 = '\0';
                  }
                  else {
                    do {
                      cVar1 = *param_3;
                      param_3 = param_3 + 1;
                      *pcVar8 = cVar1;
                      pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                  }
                  if (param_4 == (char *)0x0) {
                    pcVar8 = (char *)0x1;
                  }
                  else {
                    pcVar8 = param_4;
                    do {
                      cVar1 = *pcVar8;
                      pcVar8 = pcVar8 + 1;
                    } while (cVar1 != '\0');
                    pcVar8 = pcVar8 + (1 - (int)(param_4 + 1));
                  }
                  pcVar8 = malloc((size_t)pcVar8);
                  this->description[this->count] = pcVar8;
                  if (this->description[this->count] == (char *)0x0) {
                    free(this->email[this->count]);
                    free(this->name[this->count]);
                    free(this->url[this->count]);
                  }
                  else {
                    pcVar8 = this->description[this->count];
                    if (param_4 == (char *)0x0) {
                      *pcVar8 = '\0';
                    }
                    else {
                      do {
                        cVar1 = *param_4;
                        param_4 = param_4 + 1;
                        *pcVar8 = cVar1;
                        pcVar8 = pcVar8 + 1;
                      } while (cVar1 != '\0');
                    }
                    if (param_5 == (char *)0x0) {
                      pcVar8 = (char *)0x1;
                    }
                    else {
                      pcVar8 = param_5;
                      do {
                        cVar1 = *pcVar8;
                        pcVar8 = pcVar8 + 1;
                      } while (cVar1 != '\0');
                      pcVar8 = pcVar8 + (1 - (int)(param_5 + 1));
                    }
                    pcVar8 = malloc((size_t)pcVar8);
                    this->flag[this->count] = pcVar8;
                    if (this->flag[this->count] == (char *)0x0) {
                      free(this->email[this->count]);
                      free(this->name[this->count]);
                      free(this->url[this->count]);
                      free(this->description[this->count]);
                    }
                    else {
                      pcVar8 = this->flag[this->count];
                      if (param_5 == (char *)0x0) {
                        *pcVar8 = '\0';
                      }
                      else {
                        do {
                          cVar1 = *param_5;
                          param_5 = param_5 + 1;
                          *pcVar8 = cVar1;
                          pcVar8 = pcVar8 + 1;
                        } while (cVar1 != '\0');
                      }
                      wParam = SendMessageA((HWND)this->hwnd,0x180,0,(LPARAM)this->name[this->count]
                                           );
                      if ((wParam != 0xffffffff) && (wParam != 0xfffffffe)) {
                        LVar9 = SendMessageA((HWND)this->hwnd,0x19a,wParam,this->count);
                        if (LVar9 != -1) {
                          SendMessageA((HWND)this->hwnd,0x186,wParam,0);
                          this->count = this->count + 1;
                          InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
                          return;
                        }
                        SendMessageA((HWND)this->hwnd,0x182,wParam,0);
                      }
                      free(this->name[this->count]);
                      free(this->email[this->count]);
                      free(this->url[this->count]);
                      free(this->description[this->count]);
                      free(this->flag[this->count]);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}
