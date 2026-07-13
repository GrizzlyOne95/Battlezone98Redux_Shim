/*
 * Entry: 005cd1f9
 * Name: `WeaponClass::GetProtoList'::__l2::`dynamic_atexit_destructor_for_'protoList''
 * Namespace: `WeaponClass::GetProtoList'::__l2
 * Signature: void `dynamic_atexit_destructor_for_'protoList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl `WeaponClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__(void)

{
  std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Tidy
            ((vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *)
             &`protected:_static_class_std::vector<class_WeaponClass*,class_std::allocator<class_WeaponClass*>_>&___cdecl_WeaponClass::GetProtoList(void)'
              ::__l2::protoList);
  operator_delete(_protoList);
  return;
}
