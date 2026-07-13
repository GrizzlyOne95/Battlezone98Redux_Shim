/*
 * Entry: 0053ea1e
 * Name: ParameterDB::Get<8>
 * Namespace: ParameterDB
 * Signature: bool Get<8>(ParameterDB * this, uint param_1, uint param_2, char[8] * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get<8>(ParameterDB *this,uint param_1,uint param_2,char (*param_3) [8],char *param_4)

{
  bool bVar1;
  
  bVar1 = Get(this,param_1,param_2,*param_3,8,param_4);
  return bVar1;
}
