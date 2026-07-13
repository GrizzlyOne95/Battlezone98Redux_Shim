/*
 * Entry: 005cce41
 * Name: `ExplosionClass::GetProtoList'::__l2::`dynamic_atexit_destructor_for_'protoList''
 * Namespace: `ExplosionClass::GetProtoList'::__l2
 * Signature: void `dynamic_atexit_destructor_for_'protoList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl `ExplosionClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__(void)

{
  std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::_Tidy
            ((vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)
             &`protected:_static_class_std::vector<class_ExplosionClass*,class_std::allocator<class_ExplosionClass*>_>&___cdecl_ExplosionClass::GetProtoList(void)'
              ::__l2::protoList);
  operator_delete(_protoList);
  return;
}
