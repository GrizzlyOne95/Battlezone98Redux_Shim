/*
 * Entry: 004a32c5
 * Name: ParameterDB::Get
 * Namespace: ParameterDB
 * Signature: bool Get(ParameterDB * this, uint param_1, uint param_2, float * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
ParameterDB::Get(ParameterDB *this,uint param_1,uint param_2,float *param_3,float param_4)

{
  bool bVar1;
  char *pcVar2;
  char *unaff_EDI;
  float fVar3;
  
  pcVar2 = Get(this,param_1,param_2);
  if (pcVar2 == (char *)0x0) {
    if (param_3 != (float *)0x0) {
      *param_3 = param_4;
    }
    bVar1 = false;
  }
  else {
    if (param_3 != (float *)0x0) {
      fVar3 = GetFloat(unaff_EDI);
      *param_3 = fVar3;
    }
    bVar1 = true;
  }
  return bVar1;
}
