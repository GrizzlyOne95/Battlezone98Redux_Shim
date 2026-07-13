/*
 * Entry: 005ccfc9
 * Name: `OrdnanceClass::GetProtoList'::__l2::`dynamic_atexit_destructor_for_'protoList''
 * Namespace: `OrdnanceClass::GetProtoList'::__l2
 * Signature: void `dynamic_atexit_destructor_for_'protoList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl `OrdnanceClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__(void)

{
  std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::_Tidy
            ((vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *)
             &`protected:_static_class_std::vector<class_OrdnanceClass*,class_std::allocator<class_OrdnanceClass*>_>&___cdecl_OrdnanceClass::GetProtoList(void)'
              ::__l2::protoList);
  operator_delete(_protoList);
  return;
}
