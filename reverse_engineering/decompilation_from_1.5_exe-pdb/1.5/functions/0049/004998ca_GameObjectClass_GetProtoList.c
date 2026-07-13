/*
 * Entry: 004998ca
 * Name: GameObjectClass::GetProtoList
 * Namespace: GameObjectClass
 * Signature: vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * GetProtoList(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * __cdecl
GameObjectClass::GetProtoList(void)

{
  if ((`protected:_static_class_std::vector<class_GameObjectClass*,class_std::allocator<class_GameObjectClass*>_>&___cdecl_GameObjectClass::GetProtoList(void)'
       ::__l2::_local_static_guard__2__ & 1) == 0) {
    `protected:_static_class_std::vector<class_GameObjectClass*,class_std::allocator<class_GameObjectClass*>_>&___cdecl_GameObjectClass::GetProtoList(void)'
    ::__l2::_local_static_guard__2__ =
         `protected:_static_class_std::vector<class_GameObjectClass*,class_std::allocator<class_GameObjectClass*>_>&___cdecl_GameObjectClass::GetProtoList(void)'
         ::__l2::_local_static_guard__2__ | 1;
    std::vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
    vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
              ((vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *)
               &`protected:_static_class_std::vector<class_GameObjectClass*,class_std::allocator<class_GameObjectClass*>_>&___cdecl_GameObjectClass::GetProtoList(void)'
                ::__l2::protoList);
    atexit(`GameObjectClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__);
  }
  return (vector<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *)
         &`protected:_static_class_std::vector<class_GameObjectClass*,class_std::allocator<class_GameObjectClass*>_>&___cdecl_GameObjectClass::GetProtoList(void)'
          ::__l2::protoList;
}
