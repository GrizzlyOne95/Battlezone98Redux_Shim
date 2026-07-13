/*
 * Entry: 0045fa8a
 * Name: GetAIP
 * Namespace: Global
 * Signature: char * GetAIP(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl GetAIP(int param_1)

{
  int iVar1;
  _loaded_aip *p_Var2;
  
  iVar1 = current_aip[param_1];
  if ((-1 < iVar1) && (iVar1 < loaded_aip_count)) {
    p_Var2 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar1);
    return p_Var2->name;
  }
  return (char *)0x0;
}
