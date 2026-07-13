/*
 * Entry: 0044fab0
 * Name: Heap_Class<Strip_*,float>::Remove
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: void Remove(Heap_Class<Strip_*,float> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Heap_Class<Strip_*,float>::Remove(Heap_Class<Strip_*,float> *this,int param_1)

{
  RECORD *pRVar1;
  float fVar2;
  Strip *pSVar3;
  int iVar4;
  int iVar5;
  
  pRVar1 = this->Pool;
  iVar5 = this->Count;
  iVar4 = param_1 + 1;
  pRVar1[iVar4].Key = pRVar1[iVar5].Key;
  pRVar1[iVar4].Data = pRVar1[iVar5].Data;
  this->Count = this->Count + -1;
  fVar2 = this->Pool[iVar4].Key;
  pSVar3 = this->Pool[iVar4].Data;
  if (iVar4 <= this->Count >> 1) {
    do {
      iVar5 = iVar4 * 2;
      if ((iVar5 < this->Count) && (this->Pool[iVar4 * 2].Key < this->Pool[iVar4 * 2 + 1].Key)) {
        iVar5 = iVar5 + 1;
      }
      pRVar1 = this->Pool;
      if (pRVar1[iVar5].Key <= fVar2) break;
      pRVar1[iVar4].Key = pRVar1[iVar5].Key;
      pRVar1[iVar4].Data = pRVar1[iVar5].Data;
      iVar4 = iVar5;
    } while (iVar5 <= this->Count >> 1);
  }
  pRVar1 = this->Pool;
  pRVar1[iVar4].Key = fVar2;
  pRVar1[iVar4].Data = pSVar3;
  return;
}
