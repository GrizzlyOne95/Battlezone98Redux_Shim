/*
 * Entry: 0046f80a
 * Name: UserProcess::Save
 * Namespace: UserProcess
 * Signature: bool Save(UserProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UserProcess::Save(UserProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->cycle,4,"cycle");
  if (((bVar1) && (bVar1 = ::out(param_1,this->selectList,0x28,"selectList"), bVar1)) &&
     (bVar1 = ::out(param_1,this->selectNext,0x28,"selectNext"), bVar1)) {
    bVar1 = AiProcess::Save((AiProcess *)this,param_1);
    return bVar1;
  }
  return false;
}
