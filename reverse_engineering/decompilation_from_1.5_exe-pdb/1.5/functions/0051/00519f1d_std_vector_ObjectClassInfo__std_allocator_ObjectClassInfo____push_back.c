/*
 * Entry: 00519f1d
 * Name: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::push_back
 * Namespace: std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Signature: void push_back(vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> * this, ObjectClassInfo * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::push_back
          (vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> *this,
          ObjectClassInfo **param_1)

{
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> _Var1;
  uint uVar2;
  ObjectClassInfo **ppOVar3;
  _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_> local_c;
  
  ppOVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (ObjectClassInfo **)this;
  uVar2 = capacity(this);
  if ((uint)((int)ppOVar3 - (int)this->_Myfirst >> 2) < uVar2) {
    ppOVar3 = _Ufill(this,ppOVar3,1,param_1);
    this->_Mylast = ppOVar3;
  }
  else {
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::
    _Vector_const_iterator<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
              (&local_c,ppOVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (ObjectClassInfo **)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
