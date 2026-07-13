/*
 * Entry: 004500e0
 * Name: StripHeap::Update
 * Namespace: StripHeap
 * Signature: void Update(StripHeap * this, Strip * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall StripHeap::Update(StripHeap *this,Strip *param_1,float param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < *(int *)&this->field_0x4) {
    piVar2 = (int *)(*(int *)&this->field_0x10 + 0xc);
    while ((Strip *)*piVar2 != param_1) {
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 2;
      if (*(int *)&this->field_0x4 <= iVar1) {
        return;
      }
    }
    if (-1 < iVar1) {
      Heap_Class<Strip_*,float>::Remove((Heap_Class<Strip_*,float> *)this,iVar1);
      Heap_Class<Strip_*,float>::Push((Heap_Class<Strip_*,float> *)this,param_1,-param_2);
      param_1->open = true;
    }
  }
  return;
}
