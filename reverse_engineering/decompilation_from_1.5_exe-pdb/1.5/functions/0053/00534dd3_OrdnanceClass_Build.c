/*
 * Entry: 00534dd3
 * Name: OrdnanceClass::Build
 * Namespace: OrdnanceClass
 * Signature: Ordnance * Build(OrdnanceClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall OrdnanceClass::Build(OrdnanceClass *this,_OBJ76 *param_1)

{
  Ordnance *pOVar1;
  
  pOVar1 = operator_new(0xd8);
  if (pOVar1 == (Ordnance *)0x0) {
    pOVar1 = (Ordnance *)0x0;
  }
  else {
    pOVar1 = Ordnance::Ordnance(pOVar1,param_1,this);
  }
  return pOVar1;
}
