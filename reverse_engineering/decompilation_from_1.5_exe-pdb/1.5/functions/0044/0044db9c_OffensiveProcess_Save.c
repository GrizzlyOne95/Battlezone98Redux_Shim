/*
 * Entry: 0044db9c
 * Name: OffensiveProcess::Save
 * Namespace: OffensiveProcess
 * Signature: bool Save(OffensiveProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::Save(OffensiveProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->isFriend,1,"isFriend");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->engageRange,4,"engageRange"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->followRange,4,"followRange"), bVar1)) &&
     (((bVar1 = ::out(param_1,&this->weaponRange,4,"weaponRange"), bVar1 &&
       (bVar1 = ::out(param_1,&this->madTime,4,"madTime"), bVar1)) &&
      ((bVar1 = ::out(param_1,&this->attackUser,1,"attackUser"), bVar1 &&
       (bVar1 = UnitProcess::Save((UnitProcess *)this,param_1), bVar1)))))) {
    return true;
  }
  return false;
}
