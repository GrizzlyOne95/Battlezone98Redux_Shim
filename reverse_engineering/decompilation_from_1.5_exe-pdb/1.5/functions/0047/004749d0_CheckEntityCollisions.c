/*
 * Entry: 004749d0
 * Name: CheckEntityCollisions
 * Namespace: Global
 * Signature: void CheckEntityCollisions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CheckEntityCollisions(void)

{
  wrap_struct *pwVar1;
  wrap_struct *pwVar2;
  wrap_struct *pwVar3;
  tagENTITY *unaff_EDI;
  
  pwVar3 = DynamicEnts;
  if (DynamicEnts != (wrap_struct *)0x0) {
    do {
      CreateMovingBBoxe(pwVar3->ptr);
      pwVar3 = pwVar3->next;
      pwVar1 = DynamicEnts;
    } while (pwVar3 != (wrap_struct *)0x0);
    while (pwVar1 != (wrap_struct *)0x0) {
      pwVar1 = pwVar1->next;
      pwVar3 = pwVar1;
      while (pwVar2 = StaticEnts, pwVar3 != (wrap_struct *)0x0) {
        pwVar2 = pwVar3->next;
        CheckPair(pwVar3->ptr,unaff_EDI);
        pwVar3 = pwVar2;
      }
      while (pwVar2 != (wrap_struct *)0x0) {
        pwVar3 = pwVar2->next;
        CheckPair(pwVar2->ptr,unaff_EDI);
        pwVar2 = pwVar3;
      }
    }
  }
  return;
}
