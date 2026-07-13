/*
 * Entry: 004a3285
 * Name: ParameterDB::Get
 * Namespace: ParameterDB
 * Signature: bool Get(ParameterDB * this, uint param_1, uint param_2, long * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get(ParameterDB *this,uint param_1,uint param_2,long *param_3,long param_4)

{
  bool bVar1;
  char *_Src;
  
  _Src = Get(this,param_1,param_2);
  if (_Src == (char *)0x0) {
    if (param_3 != (long *)0x0) {
      *param_3 = param_4;
    }
    bVar1 = false;
  }
  else {
    if (param_3 != (long *)0x0) {
      sscanf(_Src,"%d",param_3);
    }
    bVar1 = true;
  }
  return bVar1;
}
