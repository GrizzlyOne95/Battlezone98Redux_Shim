/*
 * Entry: 005183fe
 * Name: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator*
 * Namespace: std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: ObjectClassInfo * * operator*(_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator*
          (_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00516ec2;
    }
  }
  iVar2 = *piVar1;
LAB_00516ec2:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(ObjectClassInfo ***)&this->field_0x4;
}
