/*
 * Entry: 004993be
 * Name: ParameterDB::Get<32>
 * Namespace: ParameterDB
 * Signature: bool Get<32>(ParameterDB * this, uint param_1, uint param_2, char[32] * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get<32>(ParameterDB *this,uint param_1,uint param_2,char (*param_3) [32],char *param_4)

{
  bool bVar1;
  
  bVar1 = Get(this,param_1,param_2,*param_3,0x20,param_4);
  return bVar1;
}
