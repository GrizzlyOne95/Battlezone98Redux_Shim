/*
 * Entry: 0048fe88
 * Name: DistributedObject::AllBuildingsSetLocal
 * Namespace: DistributedObject
 * Signature: void AllBuildingsSetLocal(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject::AllBuildingsSetLocal(void)

{
  DistributedObject *this;
  bool bVar1;
  DistributedObject **ppDVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_14;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_14,allDistributedObjectList._Myfirst,
             (_Container_base_aux *)&allDistributedObjectList);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_14,allDistributedObjectList._Mylast,
             (_Container_base_aux *)&allDistributedObjectList);
  bVar1 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
          operator==(&local_c,&local_14);
  while (!bVar1) {
    ppDVar2 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              ::operator*(&local_c);
    this = *ppDVar2;
    if (this != (DistributedObject *)0x0) {
      iVar3 = (**(code **)this->_padding_)();
      iVar3 = *(int *)(iVar3 + 0x28);
      if ((((iVar3 == 2) || (iVar3 == 10)) || (iVar3 == 7)) || (iVar3 == 5)) {
        iVar4 = (**(code **)(this->_padding_ + 0x34))();
        iVar5 = (**(code **)(this->_padding_ + 0x30))();
        if (iVar5 == iVar4) {
          SetLocal(this);
        }
      }
      if (iVar3 == 3) {
        SetLocal(this);
      }
    }
    std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    operator++(&local_c);
    std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              (&local_14,allDistributedObjectList._Mylast,
               (_Container_base_aux *)&allDistributedObjectList);
    bVar1 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
            operator==(&local_c,&local_14);
  }
  return;
}
