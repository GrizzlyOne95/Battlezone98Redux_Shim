/*
 * Entry: 004a33da
 * Name: ParameterDB::Get
 * Namespace: ParameterDB
 * Signature: bool Get(ParameterDB * this, uint param_1, uint param_2, char * * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get(ParameterDB *this,uint param_1,uint param_2,char **param_3,char *param_4)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = Get(this,param_1,param_2);
  if (pcVar3 == (char *)0x0) {
    if (param_3 != (char **)0x0) {
      if (param_4 == (char *)0x0) {
        *param_3 = (char *)0x0;
      }
      else {
        pcVar3 = param_4;
        do {
          cVar1 = *pcVar3;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = operator_new__((uint)(pcVar3 + (1 - (int)(param_4 + 1))));
        *param_3 = pcVar3;
        do {
          cVar1 = *param_4;
          param_4 = param_4 + 1;
          *pcVar3 = cVar1;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
      }
    }
    bVar2 = false;
  }
  else {
    if (param_3 != (char **)0x0) {
      pcVar4 = pcVar3;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      pcVar4 = operator_new__((uint)(pcVar4 + (1 - (int)(pcVar3 + 1))));
      *param_3 = pcVar4;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        *pcVar4 = cVar1;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    bVar2 = true;
  }
  return bVar2;
}
