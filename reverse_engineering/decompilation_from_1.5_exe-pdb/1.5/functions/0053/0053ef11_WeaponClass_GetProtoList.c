/*
 * Entry: 0053ef11
 * Name: WeaponClass::GetProtoList
 * Namespace: WeaponClass
 * Signature: vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * GetProtoList(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * __cdecl WeaponClass::GetProtoList(void)

{
  if ((`protected:_static_class_std::vector<class_WeaponClass*,class_std::allocator<class_WeaponClass*>_>&___cdecl_WeaponClass::GetProtoList(void)'
       ::__l2::_local_static_guard__2__ & 1) == 0) {
    `protected:_static_class_std::vector<class_WeaponClass*,class_std::allocator<class_WeaponClass*>_>&___cdecl_WeaponClass::GetProtoList(void)'
    ::__l2::_local_static_guard__2__ =
         `protected:_static_class_std::vector<class_WeaponClass*,class_std::allocator<class_WeaponClass*>_>&___cdecl_WeaponClass::GetProtoList(void)'
         ::__l2::_local_static_guard__2__ | 1;
    std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::
    vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
              ((vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *)
               &`protected:_static_class_std::vector<class_WeaponClass*,class_std::allocator<class_WeaponClass*>_>&___cdecl_WeaponClass::GetProtoList(void)'
                ::__l2::protoList);
    atexit(`WeaponClass::GetProtoList'::__l2::_dynamic_atexit_destructor_for__protoList__);
  }
  return (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *)
         &`protected:_static_class_std::vector<class_WeaponClass*,class_std::allocator<class_WeaponClass*>_>&___cdecl_WeaponClass::GetProtoList(void)'
          ::__l2::protoList;
}
