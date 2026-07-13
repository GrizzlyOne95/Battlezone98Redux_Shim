/*
 * Entry: 0053bb23
 * Name: TeamSwitcherClass::BuildClass
 * Namespace: TeamSwitcherClass
 * Signature: OrdnanceClass * BuildClass(TeamSwitcherClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall TeamSwitcherClass::BuildClass(TeamSwitcherClass *this,long64 param_1)

{
  TeamSwitcherClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0xb8);
  if (pTVar1 == (TeamSwitcherClass *)0x0) {
    pTVar1 = (TeamSwitcherClass *)0x0;
  }
  else {
    pTVar1 = TeamSwitcherClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pTVar1;
}
