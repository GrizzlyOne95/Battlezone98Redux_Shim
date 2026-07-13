/*
 * Entry: 00519274
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::back
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: ObjectClassInfo * * back(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectClassInfo ** __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::back
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this)

{
  ObjectClassInfo **ppOVar1;
  _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_c;
  
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator-
                    ((_Vector_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *)
                     &local_c,(int)local_14);
  ppOVar1 = _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator*
                      (_Var2._0_4_);
  return ppOVar1;
}
