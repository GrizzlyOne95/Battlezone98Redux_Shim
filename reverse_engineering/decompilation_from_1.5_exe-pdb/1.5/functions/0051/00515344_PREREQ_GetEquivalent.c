/*
 * Entry: 00515344
 * Name: PREREQ_GetEquivalent
 * Namespace: Global
 * Signature: ushort PREREQ_GetEquivalent(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl PREREQ_GetEquivalent(ushort param_1,char param_2)

{
  PREREQ_equiv *pPVar1;
  PREREQ_equiv *pPVar2;
  
  pPVar1 = PREREQ_table[param_1].equiv;
  if (pPVar1 != (PREREQ_equiv *)0x0) {
    pPVar2 = pPVar1;
    do {
      if (((int)PREREQ_table[pPVar2->type].side == teamdata[param_2].side) &&
         (pPVar2->type != param_1)) {
        return pPVar2->type;
      }
      pPVar2 = pPVar2->next;
    } while (pPVar2 != (PREREQ_equiv *)0x0);
    do {
      if ((PREREQ_table[pPVar1->type].haveplans[param_2] != '\0') && (pPVar1->type != param_1)) {
        return pPVar1->type;
      }
      pPVar1 = pPVar1->next;
    } while (pPVar1 != (PREREQ_equiv *)0x0);
  }
  return param_1;
}
