/*
 * Entry: 00539ca6
 * Name: SniperShell::Cleanup
 * Namespace: SniperShell
 * Signature: void Cleanup(SniperShell * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperShell::Cleanup(SniperShell *this)

{
  _Const_iterator<1> _Var1;
  _OBJ76 *p_Var2;
  _gas_object *p_Var3;
  SniperShell *pSStack_8;
  SniperShell *pSStack_4;
  
  pSStack_8 = this;
  pSStack_4 = this;
  remove_obj_from_tree(*(_OBJ76 **)&this->field_0x18);
  add_obj_to_tree(*(_OBJ76 **)&this->field_0x18,*(_OBJ76 **)(*(int *)&this->field_0x10 + 0x38));
  if (*(_OBJ76 **)&this->field_0xcc != (_OBJ76 *)0x0) {
    p_Var2 = get_obj_from_handle_fast(*(int *)&this->field_0xd0,*(_OBJ76 **)&this->field_0xcc);
    if (p_Var2 == (_OBJ76 *)0x0) {
      Trace("Ord owner (%s) died before ord (%s)\n");
    }
    p_Var2 = validate_obj(*(_OBJ76 **)&this->field_0xcc,(char *)(*(int *)&this->field_0x10 + 0x20));
    *(_OBJ76 **)&this->field_0xcc = p_Var2;
    if (p_Var2 != (_OBJ76 *)0x0) {
      release_obj(p_Var2,(char *)(*(int *)&this->field_0x10 + 0x20));
    }
  }
  _Var1._Ptr = *(_Node **)&this->field_0x8;
  _Var1._padding_ = (int)&pSStack_8;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::erase(&Ordnance::ordnanceList,_Var1);
  p_Var3 = FindGASObject((char *)0x0,*(_OBJ76 **)&this->field_0x18);
  while (*(_gas_object **)&this->field_0x74 = p_Var3, p_Var3 != (_gas_object *)0x0) {
    StopGASEvent(*(_gas_object **)&this->field_0x74);
    p_Var3 = FindGASObject((char *)0x0,*(_OBJ76 **)&this->field_0x18);
  }
  return;
}
