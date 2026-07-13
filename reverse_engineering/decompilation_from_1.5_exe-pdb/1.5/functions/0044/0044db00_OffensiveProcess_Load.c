/*
 * Entry: 0044db00
 * Name: OffensiveProcess::Load
 * Namespace: OffensiveProcess
 * Signature: bool Load(OffensiveProcess * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::Load(OffensiveProcess *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->isFriend,1);
  if ((((bVar1) && (bVar1 = ::in(param_1,&this->engageRange,4), bVar1)) &&
      (bVar1 = ::in(param_1,&this->followRange,4), bVar1)) &&
     (((bVar1 = ::in(param_1,&this->weaponRange,4), bVar1 &&
       (bVar1 = ::in(param_1,&this->madTime,4), bVar1)) &&
      ((bVar1 = ::in(param_1,&this->attackUser,1), bVar1 &&
       (bVar1 = UnitProcess::Load((UnitProcess *)this,param_1), bVar1)))))) {
    return true;
  }
  return false;
}
