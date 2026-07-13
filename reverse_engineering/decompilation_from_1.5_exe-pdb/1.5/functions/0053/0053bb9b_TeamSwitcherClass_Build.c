/*
 * Entry: 0053bb9b
 * Name: TeamSwitcherClass::Build
 * Namespace: TeamSwitcherClass
 * Signature: Ordnance * Build(TeamSwitcherClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall TeamSwitcherClass::Build(TeamSwitcherClass *this,_OBJ76 *param_1)

{
  TeamSwitcher *pTVar1;
  
  pTVar1 = operator_new(0x138);
  if (pTVar1 == (TeamSwitcher *)0x0) {
    pTVar1 = (TeamSwitcher *)0x0;
  }
  else {
    pTVar1 = TeamSwitcher::TeamSwitcher(pTVar1,param_1,this);
  }
  return (Ordnance *)pTVar1;
}
