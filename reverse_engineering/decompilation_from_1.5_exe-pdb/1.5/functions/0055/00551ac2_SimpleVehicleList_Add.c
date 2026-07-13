/*
 * Entry: 00551ac2
 * Name: SimpleVehicleList::Add
 * Namespace: SimpleVehicleList
 * Signature: void Add(SimpleVehicleList * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SimpleVehicleList::Add(SimpleVehicleList *this,char *param_1,char *param_2)

{
  char cVar1;
  _s *_Memory;
  _s *p_Var2;
  char *pcVar3;
  
  _Memory = this->s;
  p_Var2 = realloc(_Memory,this->count * 8 + 8);
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
      this->s[this->count].label = pcVar3;
      pcVar3 = this->s[this->count].label;
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
        this->count = this->count + 1;
      }
    }
  }
  return;
}
