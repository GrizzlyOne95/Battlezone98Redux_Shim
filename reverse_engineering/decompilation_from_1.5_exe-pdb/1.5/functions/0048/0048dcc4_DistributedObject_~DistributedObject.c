/*
 * Entry: 0048dcc4
 * Name: DistributedObject::~DistributedObject
 * Namespace: DistributedObject
 * Signature: void ~DistributedObject(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::~DistributedObject(DistributedObject *this)

{
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var1;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var2;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var3;
  map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
  *this_00;
  _Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> _Var4;
  undefined1 local_28 [8];
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_20;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_18;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_10;
  DistributedObject *local_8;
  
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_20,allDistributedObjectList._Mylast,
             (_Container_base_aux *)&allDistributedObjectList);
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_10,allDistributedObjectList._Mylast,
             (_Container_base_aux *)&allDistributedObjectList);
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_18,allDistributedObjectList._Myfirst,
             (_Container_base_aux *)&allDistributedObjectList);
  _Var4._4_4_ = local_18._padding_;
  _Var4._0_4_ = local_28;
  _Var2._4_4_ = local_10._padding_;
  _Var2._0_4_ = local_18._Myptr;
  _Var4 = std::
          remove<std::_Vector_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>,DistributedObject_*>
                    (_Var4,_Var2,local_10._Myptr);
  _Var1._Myptr = (DistributedObject **)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_20;
  _Var3._Myptr = (DistributedObject **)local_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::erase
            (&allDistributedObjectList,_Var1,_Var3);
  if (this->object_type == '\x02') {
    this_00 = &remoteDistributedObjectMap;
  }
  else {
    if (this->object_type != '\x01') {
      return;
    }
    this_00 = &localDistributedObjectMap;
  }
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           *)this_00,&this->dwLocalID);
  return;
}
