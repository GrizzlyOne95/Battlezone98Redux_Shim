/*
 * Entry: 00539ccd
 * Name: SniperShellClass::Build
 * Namespace: SniperShellClass
 * Signature: Ordnance * Build(SniperShellClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall SniperShellClass::Build(SniperShellClass *this,_OBJ76 *param_1)

{
  SniperShell *pSVar1;
  
  pSVar1 = operator_new(0xe0);
  if (pSVar1 == (SniperShell *)0x0) {
    pSVar1 = (SniperShell *)0x0;
  }
  else {
    pSVar1 = SniperShell::SniperShell(pSVar1,param_1,this);
  }
  return (Ordnance *)pSVar1;
}
