/*
 * Entry: 0045e1d7
 * Name: ExpandingArray<_loaded_aip>::operator[]
 * Namespace: ExpandingArray<_loaded_aip>
 * Signature: _loaded_aip * operator[](ExpandingArray<_loaded_aip> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_loaded_aip * __thiscall
ExpandingArray<_loaded_aip>::operator[](ExpandingArray<_loaded_aip> *this,int param_1)

{
  int iVar1;
  longlong lVar2;
  _loaded_aip *p_Var3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  
  iVar1 = this->size;
  if (iVar1 <= param_1) {
    if (iVar1 == 0) {
      p_Var3 = operator_new__(0x140);
      this->array = p_Var3;
      this->size = 0x10;
    }
    else {
      lVar2 = (ulonglong)(uint)(iVar1 * 2) * 0x14;
      p_Var3 = operator_new__(-(uint)((int)((ulonglong)lVar2 >> 0x20) != 0) | (uint)lVar2);
      iVar6 = 0;
      if (0 < this->size) {
        iVar4 = 0;
        do {
          iVar6 = iVar6 + 1;
          pcVar7 = this->array->name + iVar4;
          pcVar8 = p_Var3->name + iVar4;
          for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
            *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar8 = pcVar8 + 4;
          }
          iVar4 = iVar4 + 0x14;
        } while (iVar6 < this->size);
      }
      operator_delete(this->array);
      this->array = p_Var3;
      this->size = iVar1 * 2;
    }
  }
  return this->array + param_1;
}
