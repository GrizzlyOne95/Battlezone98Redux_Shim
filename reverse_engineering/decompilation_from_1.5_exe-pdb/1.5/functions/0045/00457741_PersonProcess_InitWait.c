/*
 * Entry: 00457741
 * Name: PersonProcess::InitWait
 * Namespace: PersonProcess
 * Signature: void InitWait(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::InitWait(PersonProcess *this)

{
  GameObject *pGVar1;
  GameObject *unaff_ESI;
  
  if (this->_padding_ != 0) {
    pGVar1 = FindBase(unaff_ESI);
    this->base = pGVar1;
    if (pGVar1 != (GameObject *)0x0) {
      this->_padding_ = 0x10;
    }
  }
  OffensiveProcess::InitWait((OffensiveProcess *)this);
  this->getIn = false;
  return;
}
