/*
 * Entry: 004993d8
 * Name: ParameterDB::Get<4>
 * Namespace: ParameterDB
 * Signature: bool Get<4>(ParameterDB * this, uint param_1, uint param_2, char[4] * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get<4>(ParameterDB *this,uint param_1,uint param_2,char (*param_3) [4],char *param_4)

{
  bool bVar1;
  
  bVar1 = Get(this,param_1,param_2,*param_3,4,param_4);
  return bVar1;
}
