/*
 * Entry: 00549b8c
 * Name: OldNew::OldNew
 * Namespace: OldNew
 * Signature: OldNew * OldNew(OldNew * this, void * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OldNew * __thiscall OldNew::OldNew(OldNew *this,void *param_1,void *param_2)

{
  list<OldNew_*,std::allocator<OldNew_*>_> *this_00;
  
  this->old_pointer = param_1;
  this->new_pointer = param_2;
  if (otable == (list<OldNew_*,std::allocator<OldNew_*>_> *)0x0) {
    this_00 = operator_new(0x1c);
    if (this_00 == (list<OldNew_*,std::allocator<OldNew_*>_> *)0x0) {
      otable = (list<OldNew_*,std::allocator<OldNew_*>_> *)0x0;
    }
    else {
      otable = std::list<OldNew_*,std::allocator<OldNew_*>_>::
               list<OldNew_*,std::allocator<OldNew_*>_>(this_00);
    }
  }
  param_1 = this;
  std::list<OldNew_*,std::allocator<OldNew_*>_>::push_back(otable,&param_1);
  return this;
}
