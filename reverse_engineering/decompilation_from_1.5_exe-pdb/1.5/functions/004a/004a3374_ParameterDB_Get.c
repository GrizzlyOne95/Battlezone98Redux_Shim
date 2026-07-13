/*
 * Entry: 004a3374
 * Name: ParameterDB::Get
 * Namespace: ParameterDB
 * Signature: bool Get(ParameterDB * this, uint param_1, uint param_2, char * param_3, uint param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get(ParameterDB *this,uint param_1,uint param_2,char *param_3,uint param_4,
                char *param_5)

{
  bool bVar1;
  char *_Source;
  
  _Source = Get(this,param_1,param_2);
  if (_Source == (char *)0x0) {
    if (param_3 != (char *)0x0) {
      if (param_5 == (char *)0x0) {
        *param_3 = '\0';
      }
      else {
        strncpy(param_3,param_5,param_4 - 1);
        param_3[param_4 - 1] = '\0';
      }
    }
    bVar1 = false;
  }
  else {
    if (param_3 != (char *)0x0) {
      strncpy(param_3,_Source,param_4 - 1);
      param_3[param_4 - 1] = '\0';
    }
    bVar1 = true;
  }
  return bVar1;
}
