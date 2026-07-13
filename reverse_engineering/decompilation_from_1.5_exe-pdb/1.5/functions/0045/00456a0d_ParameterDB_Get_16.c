/*
 * Entry: 00456a0d
 * Name: ParameterDB::Get<16>
 * Namespace: ParameterDB
 * Signature: bool Get<16>(ParameterDB * this, uint param_1, uint param_2, char[16] * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get<16>(ParameterDB *this,uint param_1,uint param_2,char (*param_3) [16],char *param_4)

{
  bool bVar1;
  
  bVar1 = Get(this,param_1,param_2,*param_3,0x10,param_4);
  return bVar1;
}
