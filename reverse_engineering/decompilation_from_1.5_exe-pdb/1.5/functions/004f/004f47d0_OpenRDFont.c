/*
 * Entry: 004f47d0
 * Name: OpenRDFont
 * Namespace: Global
 * Signature: HFONT__ * OpenRDFont(RDFONT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HFONT__ * __cdecl OpenRDFont(RDFONT *param_1)

{
  _FontSpec *p_Var1;
  HFONT__ *pHVar2;
  char *pcVar3;
  
  p_Var1 = param_1->fs[(UserProfilePtr->graphicDetail).resolution - 1];
  if (p_Var1 == (_FontSpec *)0x0) {
    return (HFONT__ *)0x0;
  }
  pcVar3 = p_Var1->specificName;
  if (pcVar3 == (char *)0x0) {
    pcVar3 = param_1->genericName;
  }
  pHVar2 = OpenFont(pcVar3,p_Var1->height);
  return pHVar2;
}
