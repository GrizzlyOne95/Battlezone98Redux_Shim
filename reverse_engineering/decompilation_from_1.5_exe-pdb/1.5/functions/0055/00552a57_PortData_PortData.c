/*
 * Entry: 00552a57
 * Name: PortData::PortData
 * Namespace: PortData
 * Signature: PortData * PortData(PortData * this, int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PortData * __thiscall PortData::PortData(PortData *this,int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  this->comport = param_1;
  if (param_2 == (char *)0x0) {
    pcVar2 = operator_new__(1);
    this->name = pcVar2;
    *pcVar2 = '\0';
  }
  else {
    pcVar2 = param_2;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = operator_new__((uint)(pcVar2 + (1 - (int)(param_2 + 1))));
    this->name = pcVar2;
    do {
      cVar1 = *param_2;
      param_2 = param_2 + 1;
      *pcVar2 = cVar1;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
  }
  return this;
}
