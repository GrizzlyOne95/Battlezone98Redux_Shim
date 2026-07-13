/*
 * Entry: 004c2e17
 * Name: CockpitTimer::Load
 * Namespace: CockpitTimer
 * Signature: bool Load(CockpitTimer * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall CockpitTimer::Load(CockpitTimer *this,_iobuf *param_1)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = ::in(param_1,&this->frac,4);
  if (bVar1) {
    bVar1 = ::in(param_1,&this->timer,4);
    if (bVar1) {
      bVar1 = ::in(param_1,&this->warn,4);
      if (bVar1) {
        bVar1 = ::in(param_1,&this->alert,4);
        if (bVar1) {
          bVar1 = ::in(param_1,&this->countdown,1);
          if (bVar1) {
            bVar1 = ::in(param_1,&this->active,1);
            if (bVar1) {
              bVar1 = ::in(param_1,&this->show,1);
              if (bVar1) {
                bVar1 = true;
                goto LAB_004c2eaa;
              }
            }
          }
        }
      }
    }
  }
  bVar1 = false;
LAB_004c2eaa:
  if ((this->countdown == false) || (0xe0f < this->timer)) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  this->hours = bVar2;
  return bVar1;
}
