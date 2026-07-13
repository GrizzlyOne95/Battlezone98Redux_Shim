/*
 * Entry: 004523f0
 * Name: PathZone::`vector_deleting_destructor'
 * Namespace: PathZone
 * Signature: void * `vector_deleting_destructor'(PathZone * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PathZone::_vector_deleting_destructor_(PathZone *this,uint param_1)

{
  uchar *puVar1;
  int iVar2;
  Strip **ppSVar3;
  Strip ***pppSVar4;
  int iVar5;
  
  if ((param_1 & 2) != 0) {
    iVar2 = *(int *)(this[-1].stripAtLocation[0xf] + 0xc);
    puVar1 = this[-1].stripAtLocation[0xf] + 0xc;
    iVar5 = iVar2 + -1;
    if (-1 < iVar5) {
      pppSVar4 = &this[iVar2].terrainStrips._Myfirst;
      do {
        if (pppSVar4[-0x49] != (void *)0x0) {
          operator_delete(pppSVar4[-0x49]);
        }
        pppSVar4[-0x49] = (Strip **)0x0;
        pppSVar4[-0x48] = (Strip **)0x0;
        pppSVar4[-0x47] = (Strip **)0x0;
        operator_delete(pppSVar4[-0x4c]);
        iVar5 = iVar5 + -1;
        pppSVar4 = pppSVar4 + -0x49;
      } while (-1 < iVar5);
    }
    if ((param_1 & 1) != 0) {
      operator_delete__(puVar1);
    }
    return puVar1;
  }
  ppSVar3 = (this->terrainStrips)._Myfirst;
  if (ppSVar3 != (Strip **)0x0) {
    operator_delete(ppSVar3);
  }
  (this->terrainStrips)._Myfirst = (Strip **)0x0;
  (this->terrainStrips)._Mylast = (Strip **)0x0;
  (this->terrainStrips)._Myend = (Strip **)0x0;
  operator_delete((void *)(this->terrainStrips)._padding_);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
