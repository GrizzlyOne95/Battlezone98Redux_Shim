/*
 * Entry: 004c2ec8
 * Name: CockpitTimer::Save
 * Namespace: CockpitTimer
 * Signature: bool Save(CockpitTimer * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall CockpitTimer::Save(CockpitTimer *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->frac,4,"frac");
  if ((((bVar1) && (bVar1 = ::out(param_1,&this->timer,4,"timer"), bVar1)) &&
      (bVar1 = ::out(param_1,&this->warn,4,"warn"), bVar1)) &&
     (((bVar1 = ::out(param_1,&this->alert,4,"alert"), bVar1 &&
       (bVar1 = ::out(param_1,&this->countdown,1,"countdown"), bVar1)) &&
      ((bVar1 = ::out(param_1,&this->active,1,"active"), bVar1 &&
       (bVar1 = ::out(param_1,&this->show,1,"show"), bVar1)))))) {
    return true;
  }
  return false;
}
