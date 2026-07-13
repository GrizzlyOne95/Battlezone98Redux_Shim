/*
 * Entry: 0044f9e0
 * Name: Heap_Class<Strip_*,float>::Pop
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: void Pop(Heap_Class<Strip_*,float> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Heap_Class<Strip_*,float>::Pop(Heap_Class<Strip_*,float> *this)

{
  RECORD *pRVar1;
  float fVar2;
  Strip *pSVar3;
  int iVar4;
  int iVar5;
  
  pRVar1 = this->Pool;
  iVar5 = this->Count;
  pRVar1[1].Key = pRVar1[iVar5].Key;
  pRVar1[1].Data = pRVar1[iVar5].Data;
  this->Count = this->Count + -1;
  fVar2 = this->Pool[1].Key;
  pSVar3 = this->Pool[1].Data;
  iVar5 = 1;
  if (1 < (int)(this->Count & 0xfffffffeU)) {
    do {
      iVar4 = iVar5 * 2;
      if ((iVar4 < this->Count) && (this->Pool[iVar5 * 2].Key < this->Pool[iVar5 * 2 + 1].Key)) {
        iVar4 = iVar4 + 1;
      }
      pRVar1 = this->Pool;
      if (pRVar1[iVar4].Key <= fVar2) break;
      pRVar1[iVar5].Key = pRVar1[iVar4].Key;
      pRVar1[iVar5].Data = pRVar1[iVar4].Data;
      iVar5 = iVar4;
    } while (iVar4 <= this->Count >> 1);
  }
  pRVar1 = this->Pool;
  pRVar1[iVar5].Key = fVar2;
  pRVar1[iVar5].Data = pSVar3;
  return;
}
