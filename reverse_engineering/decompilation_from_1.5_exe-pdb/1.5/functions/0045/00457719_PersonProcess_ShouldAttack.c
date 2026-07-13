/*
 * Entry: 00457719
 * Name: PersonProcess::ShouldAttack
 * Namespace: PersonProcess
 * Signature: bool ShouldAttack(PersonProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PersonProcess::ShouldAttack(PersonProcess *this,State param_1)

{
  bool bVar1;
  GameObject *pGVar2;
  GameObject *unaff_ESI;
  
  if (param_1 == WAIT) {
    pGVar2 = FindBase(unaff_ESI);
    this->base = pGVar2;
    if (pGVar2 == (GameObject *)0x0) {
      bVar1 = OffensiveProcess::WaitVsAttack((OffensiveProcess *)this);
      return bVar1;
    }
  }
  return false;
}
