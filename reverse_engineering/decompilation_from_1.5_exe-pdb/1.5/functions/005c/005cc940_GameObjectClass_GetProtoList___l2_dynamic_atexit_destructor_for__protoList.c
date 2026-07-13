/*
 * Entry: 005cc940
 * Name: `GameObjectClass::GetProtoList'::__l2::`dynamic_atexit_destructor_for_'protoList''
 * Namespace: `GameObjectClass::GetProtoList'::__l2
 * Signature: void `dynamic_atexit_destructor_for_'protoList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
`GameObjectClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__(void)

{
  std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Tidy
            ((vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *)
             &`protected:_static_class_std::vector<class_GameObjectClass*,class_std::allocator<class_GameObjectClass*>_>&___cdecl_GameObjectClass::GetProtoList(void)'
              ::__l2::protoList);
  operator_delete(_protoList);
  return;
}
