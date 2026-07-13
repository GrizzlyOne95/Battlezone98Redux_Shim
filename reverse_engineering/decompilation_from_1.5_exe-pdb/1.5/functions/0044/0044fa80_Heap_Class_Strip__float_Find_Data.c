/*
 * Entry: 0044fa80
 * Name: Heap_Class<Strip_*,float>::Find_Data
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: int Find_Data(Heap_Class<Strip_*,float> * this, Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Heap_Class<Strip_*,float>::Find_Data(Heap_Class<Strip_*,float> *this,Strip *param_1)

{
  int iVar1;
  Strip **ppSVar2;
  
  iVar1 = 0;
  if (0 < this->Count) {
    ppSVar2 = &this->Pool[1].Data;
    do {
      if (*ppSVar2 == param_1) {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      ppSVar2 = ppSVar2 + 2;
    } while (iVar1 < this->Count);
  }
  return -1;
}
