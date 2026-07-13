/*
 * Entry: 0053b386
 * Name: LeaderRoundClass::Build
 * Namespace: LeaderRoundClass
 * Signature: Ordnance * Build(LeaderRoundClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall LeaderRoundClass::Build(LeaderRoundClass *this,_OBJ76 *param_1)

{
  LeaderRound *pLVar1;
  
  pLVar1 = operator_new(0x138);
  if (pLVar1 == (LeaderRound *)0x0) {
    pLVar1 = (LeaderRound *)0x0;
  }
  else {
    pLVar1 = LeaderRound::LeaderRound(pLVar1,param_1,this);
  }
  return (Ordnance *)pLVar1;
}
