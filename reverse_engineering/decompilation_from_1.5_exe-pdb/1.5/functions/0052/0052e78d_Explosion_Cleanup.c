/*
 * Entry: 0052e78d
 * Name: Explosion::Cleanup
 * Namespace: Explosion
 * Signature: void Cleanup(Explosion * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Explosion::Cleanup(Explosion *this)

{
  _Const_iterator<1> _Var1;
  Explosion *local_8;
  Explosion *pEStack_4;
  
  local_8 = this;
  pEStack_4 = this;
  remove_obj_from_tree(this->obj);
  add_obj_to_tree(this->obj,this->explosionClass->freeObj);
  if (this->owner != (_OBJ76 *)0x0) {
    release_obj(this->owner,".\\fun3d\\Explosion.cpp");
  }
  _Var1._Ptr = *(_Node **)&this->me;
  _Var1._padding_ = (int)&local_8;
  std::list<Explosion_*,std::allocator<Explosion_*>_>::erase(&explosionList,_Var1);
  return;
}
