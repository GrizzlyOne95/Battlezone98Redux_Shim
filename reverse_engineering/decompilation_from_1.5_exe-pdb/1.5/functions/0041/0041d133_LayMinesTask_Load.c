/*
 * Entry: 0041d133
 * Name: LayMinesTask::Load
 * Namespace: LayMinesTask
 * Signature: bool Load(LayMinesTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LayMinesTask::Load(LayMinesTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->mineCount,4);
  if ((((((bVar1) && (bVar1 = ::in(param_1,&this->radiusInc,4), bVar1)) &&
        (bVar1 = ::in(param_1,&this->angleDec,4), bVar1)) &&
       ((bVar1 = ::in(param_1,&this->mine,4), bVar1 &&
        (bVar1 = ::in(param_1,&this->radius,4), bVar1)))) &&
      ((bVar1 = ::in(param_1,&this->angle,4), bVar1 &&
       ((bVar1 = ::in(param_1,&this->angleInc,4), bVar1 &&
        (bVar1 = ::in(param_1,&this->center,0xc), bVar1)))))) &&
     (bVar1 = GoPoints::Load((GoPoints *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
