/*
 * Entry: 0041d213
 * Name: LayMinesTask::Save
 * Namespace: LayMinesTask
 * Signature: bool Save(LayMinesTask * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LayMinesTask::Save(LayMinesTask *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->mineCount,4,"mineCount");
  if ((((((bVar1) && (bVar1 = ::out(param_1,&this->radiusInc,4,"radiusInc"), bVar1)) &&
        (bVar1 = ::out(param_1,&this->angleDec,4,"angleDec"), bVar1)) &&
       ((bVar1 = ::out(param_1,&this->mine,4,"mine"), bVar1 &&
        (bVar1 = ::out(param_1,&this->radius,4,"radius"), bVar1)))) &&
      ((bVar1 = ::out(param_1,&this->angle,4,"angle"), bVar1 &&
       ((bVar1 = ::out(param_1,&this->angleInc,4,"angleInc"), bVar1 &&
        (bVar1 = ::out(param_1,&this->center,0xc,"center"), bVar1)))))) &&
     (bVar1 = GoPoints::Save((GoPoints *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
