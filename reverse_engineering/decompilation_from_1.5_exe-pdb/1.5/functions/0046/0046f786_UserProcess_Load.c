/*
 * Entry: 0046f786
 * Name: UserProcess::Load
 * Namespace: UserProcess
 * Signature: bool Load(UserProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UserProcess::Load(UserProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->cycle,4);
  if ((((bVar1) ||
       ((bVar1 = in_ptr(param_1,&dummyPtr,4,"dummyPtr",this), bVar1 &&
        (bVar1 = ::in(param_1,&this->cycle,4), bVar1)))) &&
      (bVar1 = ::in(param_1,this->selectList,0x28), bVar1)) &&
     ((bVar1 = ::in(param_1,this->selectNext,0x28), bVar1 &&
      (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
