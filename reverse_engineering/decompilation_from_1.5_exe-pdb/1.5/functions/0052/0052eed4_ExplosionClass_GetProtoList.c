/*
 * Entry: 0052eed4
 * Name: ExplosionClass::GetProtoList
 * Namespace: ExplosionClass
 * Signature: vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * GetProtoList(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * __cdecl
ExplosionClass::GetProtoList(void)

{
  if (((uint)`protected:_static_class_std::vector<class_ExplosionClass*,class_std::allocator<class_ExplosionClass*>_>&___cdecl_ExplosionClass::GetProtoList(void)'
             ::__l2::_local_static_guard__2__ & 1) == 0) {
    `protected:_static_class_std::vector<class_ExplosionClass*,class_std::allocator<class_ExplosionClass*>_>&___cdecl_ExplosionClass::GetProtoList(void)'
    ::__l2::_local_static_guard__2__._0_4_ =
         (uint)`protected:_static_class_std::vector<class_ExplosionClass*,class_std::allocator<class_ExplosionClass*>_>&___cdecl_ExplosionClass::GetProtoList(void)'
               ::__l2::_local_static_guard__2__ | 1;
    std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::
    vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
              ((vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)
               &`protected:_static_class_std::vector<class_ExplosionClass*,class_std::allocator<class_ExplosionClass*>_>&___cdecl_ExplosionClass::GetProtoList(void)'
                ::__l2::protoList);
    atexit(`ExplosionClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__);
  }
  return (vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *)
         &`protected:_static_class_std::vector<class_ExplosionClass*,class_std::allocator<class_ExplosionClass*>_>&___cdecl_ExplosionClass::GetProtoList(void)'
          ::__l2::protoList;
}
