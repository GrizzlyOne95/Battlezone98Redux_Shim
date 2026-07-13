/*
 * Entry: 005343c8
 * Name: Ordnance::Cleanup
 * Namespace: Ordnance
 * Signature: void Cleanup(Ordnance * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Ordnance::Cleanup(Ordnance *this)

{
  _Const_iterator<1> _Var1;
  _OBJ76 *p_Var2;
  _gas_object *p_Var3;
  Ordnance *local_8;
  Ordnance *pOStack_4;
  
  local_8 = this;
  pOStack_4 = this;
  remove_obj_from_tree(this->obj);
  add_obj_to_tree(this->obj,this->ordnanceClass->freeOrd);
  if (this->owner != (_OBJ76 *)0x0) {
    p_Var2 = get_obj_from_handle_fast(this->ownerHandle,this->owner);
    if (p_Var2 == (_OBJ76 *)0x0) {
      Trace("Ord owner (%s) died before ord (%s)\n");
    }
    p_Var2 = validate_obj(this->owner,this->ordnanceClass->odf);
    this->owner = p_Var2;
    if (p_Var2 != (_OBJ76 *)0x0) {
      release_obj(p_Var2,this->ordnanceClass->odf);
    }
  }
  _Var1._Ptr = *(_Node **)&this->me;
  _Var1._padding_ = (int)&local_8;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::erase(&ordnanceList,_Var1);
  p_Var3 = FindGASObject((char *)0x0,this->obj);
  while (this->go = p_Var3, p_Var3 != (_gas_object *)0x0) {
    StopGASEvent(this->go);
    p_Var3 = FindGASObject((char *)0x0,this->obj);
  }
  return;
}
