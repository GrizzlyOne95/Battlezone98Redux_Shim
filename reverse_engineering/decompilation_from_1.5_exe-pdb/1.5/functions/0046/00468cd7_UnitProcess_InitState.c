/*
 * Entry: 00468cd7
 * Name: UnitProcess::InitState
 * Namespace: UnitProcess
 * Signature: void InitState(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitState(UnitProcess *this)

{
  switch(this->curState) {
  case WAIT:
                    /* WARNING: Could not recover jumptable at 0x00468ceb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x30))();
    return;
  case GOTO:
                    /* WARNING: Could not recover jumptable at 0x00468cf0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x3c))();
    return;
  case PATROL:
                    /* WARNING: Could not recover jumptable at 0x00468cf5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x48))();
    return;
  case STAGE:
                    /* WARNING: Could not recover jumptable at 0x00468cfa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x54))();
    return;
  case ATTACK:
                    /* WARNING: Could not recover jumptable at 0x00468cff. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x60))();
    return;
  case FOLLOW:
                    /* WARNING: Could not recover jumptable at 0x00468d04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x6c))();
    return;
  case DEFEND:
                    /* WARNING: Could not recover jumptable at 0x00468d09. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x78))();
    return;
  case REPAIR:
                    /* WARNING: Could not recover jumptable at 0x00468d0e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x84))();
    return;
  case RELOAD:
                    /* WARNING: Could not recover jumptable at 0x00468d16. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x90))();
    return;
  case RESCUE:
                    /* WARNING: Could not recover jumptable at 0x00468d1e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x9c))();
    return;
  case RECYCLE:
                    /* WARNING: Could not recover jumptable at 0x00468d26. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xa8))();
    return;
  case PACKUP:
                    /* WARNING: Could not recover jumptable at 0x00468d2e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xb4))();
    return;
  case SUBATTACK:
                    /* WARNING: Could not recover jumptable at 0x00468d36. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xc0))();
    return;
  case USTATE1:
                    /* WARNING: Could not recover jumptable at 0x00468d3e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xcc))();
    return;
  case USTATE2:
                    /* WARNING: Could not recover jumptable at 0x00468d46. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xd8))();
    return;
  default:
    return;
  }
}
