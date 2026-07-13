/*
 * Entry: 004983b8
 * Name: GameObject::~GameObject
 * Namespace: GameObject
 * Signature: void ~GameObject(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::~GameObject(GameObject *this)

{
  Scanner *this_00;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var1;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var2;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var3;
  _Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> _Var4;
  undefined1 local_28 [8];
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  GameObject *local_8;
  
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  local_8 = this;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_20,objectList->_Mylast,(_Container_base_aux *)objectList);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_10,objectList->_Mylast,(_Container_base_aux *)objectList);
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,objectList->_Myfirst,(_Container_base_aux *)objectList);
  _Var4._4_4_ = local_18._padding_;
  _Var4._0_4_ = local_28;
  _Var2._4_4_ = local_10._padding_;
  _Var2._0_4_ = local_18._Myptr;
  _Var4 = std::
          remove<std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>,GameObject_*>
                    (_Var4,_Var2,local_10._Myptr);
  _Var1._Myptr = (GameObject **)*_Var4._0_4_;
  _Var1._padding_ = (int)&local_20;
  _Var3._Myptr = (GameObject **)local_20._padding_;
  _Var3._padding_ = _Var4._0_4_[1];
  std::vector<GameObject_*,std::allocator<GameObject_*>_>::erase(objectList,_Var1,_Var3);
  SetObjective(this,false);
  if (this->teamSlot != -1) {
    Team::SetSlot(this->teamList,this->teamSlot,(GameObject *)0x0);
  }
  if (this->aiProcess != (AiProcess *)0x0) {
    (**(code **)this->aiProcess->_padding_)(1,local_20._Myptr);
  }
  if (this->name != (char *)0x0) {
    operator_delete__(this->name);
  }
  if (this->label != (char *)0x0) {
    operator_delete__(this->label);
  }
  this_00 = this->scanner;
  if (this_00 != (Scanner *)0x0) {
    Scanner::~Scanner(this_00);
    ::operator_delete(this_00);
  }
  if (this->jammer != (Jammer *)0x0) {
    ::operator_delete(this->jammer);
  }
  if (this == userObject) {
    userObject = (GameObject *)0x0;
  }
  if (this->tug != (GameObject *)0x0) {
    this->tug[1].hitOrdClass = (OrdnanceClass *)0x0;
  }
  this->obj->gameObj = (void *)0x0;
  DistributedObject::~DistributedObject((DistributedObject *)&this->_padding_);
  Attachable::~Attachable((Attachable *)this);
  return;
}
