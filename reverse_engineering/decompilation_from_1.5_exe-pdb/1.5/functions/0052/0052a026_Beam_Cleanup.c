/*
 * Entry: 0052a026
 * Name: Beam::Cleanup
 * Namespace: Beam
 * Signature: void Cleanup(Beam * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Beam::Cleanup(Beam *this)

{
  _Const_iterator<1> _Var1;
  _OBJ76 *p_Var2;
  _gas_object *p_Var3;
  Beam *pBStack_8;
  Beam *pBStack_4;
  
  pBStack_8 = this;
  pBStack_4 = this;
  remove_obj_from_tree((_OBJ76 *)this->_padding_);
  add_obj_to_tree((_OBJ76 *)this->_padding_,*(_OBJ76 **)(this->_padding_ + 0x38));
  if ((_OBJ76 *)this->_padding_ != (_OBJ76 *)0x0) {
    p_Var2 = get_obj_from_handle_fast(this->_padding_,(_OBJ76 *)this->_padding_);
    if (p_Var2 == (_OBJ76 *)0x0) {
      Trace("Ord owner (%s) died before ord (%s)\n");
    }
    p_Var2 = validate_obj((_OBJ76 *)this->_padding_,(char *)(this->_padding_ + 0x20));
    this->_padding_ = (int)p_Var2;
    if (p_Var2 != (_OBJ76 *)0x0) {
      release_obj(p_Var2,(char *)(this->_padding_ + 0x20));
    }
  }
  _Var1._Ptr = (_Node *)this->_padding_;
  _Var1._padding_ = (int)&pBStack_8;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::erase(&Ordnance::ordnanceList,_Var1);
  p_Var3 = FindGASObject((char *)0x0,(_OBJ76 *)this->_padding_);
  while (this->_padding_ = (int)p_Var3, p_Var3 != (_gas_object *)0x0) {
    StopGASEvent((_gas_object *)this->_padding_);
    p_Var3 = FindGASObject((char *)0x0,(_OBJ76 *)this->_padding_);
  }
  return;
}
