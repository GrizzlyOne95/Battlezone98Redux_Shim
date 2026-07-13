/*
 * Entry: 0044f940
 * Name: Heap_Class<Strip_*,float>::Push
 * Namespace: Heap_Class<Strip_*,float>
 * Signature: void Push(Heap_Class<Strip_*,float> * this, Strip * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
Heap_Class<Strip_*,float>::Push(Heap_Class<Strip_*,float> *this,Strip *param_1,float param_2)

{
  float fVar1;
  Strip *pSVar2;
  RECORD *pRVar3;
  int iVar4;
  int iVar5;
  
  if (this->Max_Count + -1 <= this->Count) {
    if (!`public:_void___thiscall_Heap_Class<struct_Strip*,float>::Push(struct_Strip*,float)'::__l11
         ::s_Spammed) {
      `public:_void___thiscall_Heap_Class<struct_Strip*,float>::Push(struct_Strip*,float)'::__l11::
      s_Spammed = true;
    }
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  iVar4 = this->Count + 1;
  this->Count = iVar4;
  this->Pool[iVar4].Key = param_2;
  this->Pool[this->Count].Data = param_1;
  iVar4 = this->Count;
  fVar1 = this->Pool[iVar4].Key;
  pSVar2 = this->Pool[iVar4].Data;
  while (0 < iVar4) {
    pRVar3 = this->Pool;
    iVar5 = iVar4 >> 1;
    if (fVar1 < pRVar3[iVar5].Key) break;
    pRVar3[iVar4].Key = pRVar3[iVar5].Key;
    pRVar3[iVar4].Data = pRVar3[iVar5].Data;
    iVar4 = iVar5;
  }
  pRVar3 = this->Pool;
  pRVar3[iVar4].Key = fVar1;
  pRVar3[iVar4].Data = pSVar2;
  return;
}
