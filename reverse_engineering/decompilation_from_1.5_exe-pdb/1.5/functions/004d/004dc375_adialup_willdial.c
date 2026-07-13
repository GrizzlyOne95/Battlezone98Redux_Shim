/*
 * Entry: 004dc375
 * Name: adialup_willdial
 * Namespace: Global
 * Signature: int adialup_willdial(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl adialup_willdial(void)

{
  int iVar1;
  
  iVar1 = adialup_autodial_enabled();
  if (iVar1 != 0) {
    iVar1 = adialup_is_active();
    if (iVar1 == 0) {
      return 1;
    }
  }
  return 0;
}
