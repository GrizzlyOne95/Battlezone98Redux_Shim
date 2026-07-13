/*
 * Entry: 0053550d
 * Name: OrdnanceClass::GetProtoList
 * Namespace: OrdnanceClass
 * Signature: vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * GetProtoList(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> * __cdecl OrdnanceClass::GetProtoList(void)

{
  if (((uint)`protected:_static_class_std::vector<class_OrdnanceClass*,class_std::allocator<class_OrdnanceClass*>_>&___cdecl_OrdnanceClass::GetProtoList(void)'
             ::__l2::_local_static_guard__2__ & 1) == 0) {
    `protected:_static_class_std::vector<class_OrdnanceClass*,class_std::allocator<class_OrdnanceClass*>_>&___cdecl_OrdnanceClass::GetProtoList(void)'
    ::__l2::_local_static_guard__2__._0_4_ =
         (uint)`protected:_static_class_std::vector<class_OrdnanceClass*,class_std::allocator<class_OrdnanceClass*>_>&___cdecl_OrdnanceClass::GetProtoList(void)'
               ::__l2::_local_static_guard__2__ | 1;
    std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::
    vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
              ((vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *)
               &`protected:_static_class_std::vector<class_OrdnanceClass*,class_std::allocator<class_OrdnanceClass*>_>&___cdecl_OrdnanceClass::GetProtoList(void)'
                ::__l2::protoList);
    atexit(`OrdnanceClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__);
  }
  return (vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *)
         &`protected:_static_class_std::vector<class_OrdnanceClass*,class_std::allocator<class_OrdnanceClass*>_>&___cdecl_OrdnanceClass::GetProtoList(void)'
          ::__l2::protoList;
}
