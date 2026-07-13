/*
 * Entry: 00481179
 * Name: SortSound
 * Namespace: Global
 * Signature: void SortSound(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SortSound(_gas_object *param_1)

{
  _gas_object *p_Var1;
  int iVar2;
  int iVar3;
  _gas_object **pp_Var4;
  _gas_object *p_Var5;
  _gas_object *p_Var6;
  _gas_object *p_Var7;
  _gas_object *p_Var8;
  
  p_Var5 = firstSound;
  p_Var1 = firstSound->next;
  if (p_Var1 != (_gas_object *)0x0) {
    p_Var7 = (_gas_object *)0x0;
    if (p_Var1 != (_gas_object *)0x0) {
      iVar2 = (firstSound->gpi).pri;
      p_Var6 = p_Var1;
      p_Var8 = p_Var7;
      do {
        p_Var7 = p_Var6;
        iVar3 = (p_Var7->gpi).pri;
        if (iVar2 != iVar3 && iVar3 <= iVar2) {
          pp_Var4 = &firstSound->next;
          firstSound = p_Var1;
          *pp_Var4 = p_Var7;
          if (p_Var8 == (_gas_object *)0x0) {
            firstSound = p_Var5;
            return;
          }
          goto LAB_004811a9;
        }
        if (iVar2 == iVar3) {
          pp_Var4 = &firstSound->next;
          firstSound = p_Var1;
          *pp_Var4 = p_Var7->next;
          p_Var7->next = p_Var5;
          return;
        }
        p_Var6 = p_Var7->next;
        p_Var8 = p_Var7;
      } while (p_Var7->next != (_gas_object *)0x0);
    }
    pp_Var4 = &firstSound->next;
    firstSound = p_Var1;
    *pp_Var4 = (_gas_object *)0x0;
    p_Var8 = p_Var7;
LAB_004811a9:
    p_Var8->next = p_Var5;
  }
  return;
}
