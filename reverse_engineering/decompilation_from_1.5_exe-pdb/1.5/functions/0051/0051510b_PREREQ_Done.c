/*
 * Entry: 0051510b
 * Name: PREREQ_Done
 * Namespace: Global
 * Signature: void PREREQ_Done(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Done(void)

{
  PREREQ_equiv *_Memory;
  int iVar1;
  int iVar2;
  PREREQ_equiv *pPVar3;
  
  if (PREREQ_online != '\0') {
    iVar1 = 1;
    if (1 < PREREQ_maxassigned) {
      iVar2 = 0x9c;
      do {
        free(*(void **)((int)PREREQ_table->howmany + iVar2 + -0x10));
        free(*(void **)((int)PREREQ_table->howmany + iVar2 + -0xc));
        free(*(void **)((int)PREREQ_table->howmany + iVar2 + -8));
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x9c;
      } while (iVar1 < PREREQ_maxassigned);
    }
    iVar1 = 0;
    if (0 < PREREQ_maxequiv) {
      do {
        _Memory = PREREQ_equiv_table[iVar1];
        if (_Memory != (PREREQ_equiv *)0x0) {
          pPVar3 = _Memory->next;
          while( true ) {
            free(_Memory);
            if (pPVar3 == (PREREQ_equiv *)0x0) break;
            _Memory = pPVar3;
            pPVar3 = pPVar3->next;
          }
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < PREREQ_maxequiv);
    }
    free(PREREQ_equiv_table);
    free(PREREQ_table);
    PREREQ_online = '\0';
  }
  return;
}
