/*
 * Entry: 00551785
 * Name: VehicleList::Add
 * Namespace: VehicleList
 * Signature: void Add(VehicleList * this, char * param_1, char * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
VehicleList::Add(VehicleList *this,char *param_1,char *param_2,char *param_3,char *param_4)

{
  char cVar1;
  _s *_Memory;
  _s *p_Var2;
  char *pcVar3;
  
  _Memory = this->s;
  p_Var2 = realloc(_Memory,(this->count + 1) * 0x10);
  this->s = p_Var2;
  if (p_Var2 == (_s *)0x0) {
    this->s = _Memory;
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
    pcVar3 = malloc((size_t)pcVar3);
    this->s[this->count].name = pcVar3;
    pcVar3 = this->s[this->count].name;
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
      if (param_2 == (char *)0x0) {
        pcVar3 = (char *)0x1;
      }
      else {
        pcVar3 = param_2;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = pcVar3 + (1 - (int)(param_2 + 1));
      }
      pcVar3 = malloc((size_t)pcVar3);
      this->s[this->count].description = pcVar3;
      pcVar3 = this->s[this->count].description;
      if (pcVar3 == (char *)0x0) {
        free(this->s[this->count].name);
      }
      else {
        if (param_2 == (char *)0x0) {
          *pcVar3 = '\0';
        }
        else {
          do {
            cVar1 = *param_2;
            param_2 = param_2 + 1;
            *pcVar3 = cVar1;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
        }
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
        pcVar3 = malloc((size_t)pcVar3);
        this->s[this->count].label = pcVar3;
        pcVar3 = this->s[this->count].label;
        if (pcVar3 == (char *)0x0) {
          free(this->s[this->count].name);
          free(this->s[this->count].description);
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
          if (param_3 == (char *)0x0) {
            pcVar3 = (char *)0x1;
          }
          else {
            pcVar3 = param_3;
            do {
              cVar1 = *pcVar3;
              pcVar3 = pcVar3 + 1;
            } while (cVar1 != '\0');
            pcVar3 = pcVar3 + (1 - (int)(param_3 + 1));
          }
          pcVar3 = malloc((size_t)pcVar3);
          this->s[this->count].avi = pcVar3;
          pcVar3 = this->s[this->count].avi;
          if (pcVar3 == (char *)0x0) {
            free(this->s[this->count].name);
            free(this->s[this->count].description);
            free(this->s[this->count].avi);
          }
          else {
            if (param_3 == (char *)0x0) {
              *pcVar3 = '\0';
            }
            else {
              do {
                cVar1 = *param_3;
                param_3 = param_3 + 1;
                *pcVar3 = cVar1;
                pcVar3 = pcVar3 + 1;
              } while (cVar1 != '\0');
            }
            this->count = this->count + 1;
          }
        }
      }
    }
  }
  return;
}
