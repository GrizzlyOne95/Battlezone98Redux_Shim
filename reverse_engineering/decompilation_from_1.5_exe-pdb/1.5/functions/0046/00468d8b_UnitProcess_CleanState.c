/*
 * Entry: 00468d8b
 * Name: UnitProcess::CleanState
 * Namespace: UnitProcess
 * Signature: void CleanState(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::CleanState(UnitProcess *this)

{
  switch(this->curState) {
  case WAIT:
                    /* WARNING: Could not recover jumptable at 0x00468d9f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x34))();
    return;
  case GOTO:
                    /* WARNING: Could not recover jumptable at 0x00468da4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x40))();
    return;
  case PATROL:
                    /* WARNING: Could not recover jumptable at 0x00468da9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x4c))();
    return;
  case STAGE:
                    /* WARNING: Could not recover jumptable at 0x00468dae. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x58))();
    return;
  case ATTACK:
                    /* WARNING: Could not recover jumptable at 0x00468db3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 100))();
    return;
  case FOLLOW:
                    /* WARNING: Could not recover jumptable at 0x00468db8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x70))();
    return;
  case DEFEND:
                    /* WARNING: Could not recover jumptable at 0x00468dbd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x7c))();
    return;
  case REPAIR:
                    /* WARNING: Could not recover jumptable at 0x00468dc2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x88))();
    return;
  case RELOAD:
                    /* WARNING: Could not recover jumptable at 0x00468dca. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x94))();
    return;
  case RESCUE:
                    /* WARNING: Could not recover jumptable at 0x00468dd2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xa0))();
    return;
  case RECYCLE:
                    /* WARNING: Could not recover jumptable at 0x00468dda. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xac))();
    return;
  case PACKUP:
                    /* WARNING: Could not recover jumptable at 0x00468de2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xb8))();
    return;
  case SUBATTACK:
                    /* WARNING: Could not recover jumptable at 0x00468dea. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xc4))();
    return;
  case USTATE1:
                    /* WARNING: Could not recover jumptable at 0x00468df2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xd0))();
    return;
  case USTATE2:
                    /* WARNING: Could not recover jumptable at 0x00468dfa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0xdc))();
    return;
  default:
    return;
  }
}
