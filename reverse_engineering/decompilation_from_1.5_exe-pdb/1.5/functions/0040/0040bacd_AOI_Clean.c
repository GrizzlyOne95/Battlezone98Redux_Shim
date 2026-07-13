/*
 * Entry: 0040bacd
 * Name: AOI::Clean
 * Namespace: AOI
 * Signature: void Clean(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AOI::Clean(void)

{
  AOI *this;
  AOI **ppAVar1;
  int *(*papiVar2) [16];
  int **ppiVar3;
  int iVar4;
  
  papiVar2 = values;
  do {
    iVar4 = 0x10;
    do {
      if ((*papiVar2)[0] != (int *)0x0) {
        operator_delete__((*papiVar2)[0]);
        (*papiVar2)[0] = (int *)0x0;
      }
      papiVar2 = (int *(*) [16])((int)papiVar2 + 4);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  } while ((int)papiVar2 < 0x64dfe8);
  ppiVar3 = forces;
  do {
    if (*ppiVar3 != (int *)0x0) {
      operator_delete(*ppiVar3);
      *ppiVar3 = (int *)0x0;
    }
    ppiVar3 = ppiVar3 + 1;
  } while ((int)ppiVar3 < 0x64df68);
  while (areas._Mysize != 0) {
    ppAVar1 = std::list<AOI_*,std::allocator<AOI_*>_>::back(&areas);
    this = *ppAVar1;
    if (this != (AOI *)0x0) {
      ~AOI(this);
      operator_delete(this);
    }
  }
  return;
}
