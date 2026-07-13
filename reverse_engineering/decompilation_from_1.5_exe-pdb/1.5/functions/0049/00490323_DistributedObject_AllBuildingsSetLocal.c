/*
 * Entry: 00490323
 * Name: DistributedObject_AllBuildingsSetLocal
 * Namespace: Global
 * Signature: void DistributedObject_AllBuildingsSetLocal(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject_AllBuildingsSetLocal(void)

{
  DistributedObject *this;
  bool bVar1;
  DistributedObject **ppDVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Stack_14;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Stack_c;
  
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&_Stack_14,DistributedObject::allDistributedObjectList._Myfirst,
             (_Container_base_aux *)&DistributedObject::allDistributedObjectList);
  _Stack_c._padding_ = _Stack_14._padding_;
  _Stack_c._Myptr = _Stack_14._Myptr;
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&_Stack_14,DistributedObject::allDistributedObjectList._Mylast,
             (_Container_base_aux *)&DistributedObject::allDistributedObjectList);
  bVar1 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
          operator==(&_Stack_c,&_Stack_14);
  while (!bVar1) {
    ppDVar2 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              ::operator*(&_Stack_c);
    this = *ppDVar2;
    if (this != (DistributedObject *)0x0) {
      iVar3 = (**(code **)this->_padding_)();
      iVar3 = *(int *)(iVar3 + 0x28);
      if ((((iVar3 == 2) || (iVar3 == 10)) || (iVar3 == 7)) || (iVar3 == 5)) {
        iVar4 = (**(code **)(this->_padding_ + 0x34))();
        iVar5 = (**(code **)(this->_padding_ + 0x30))();
        if (iVar5 == iVar4) {
          DistributedObject::SetLocal(this);
        }
      }
      if (iVar3 == 3) {
        DistributedObject::SetLocal(this);
      }
    }
    std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    operator++(&_Stack_c);
    std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              (&_Stack_14,DistributedObject::allDistributedObjectList._Mylast,
               (_Container_base_aux *)&DistributedObject::allDistributedObjectList);
    bVar1 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
            operator==(&_Stack_c,&_Stack_14);
  }
  return;
}
