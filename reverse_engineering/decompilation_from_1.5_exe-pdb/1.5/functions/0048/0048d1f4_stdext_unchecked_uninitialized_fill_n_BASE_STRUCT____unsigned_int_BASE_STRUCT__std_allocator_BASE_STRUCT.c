/*
 * Entry: 0048d1f4
 * Name: stdext::unchecked_uninitialized_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*,std::allocator<BASE_STRUCT_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*,std::allocator<BASE_STRUCT_*>_>(BASE_STRUCT * * param_1, uint param_2, BASE_STRUCT * * param_3, allocator<BASE_STRUCT_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*,std::allocator<BASE_STRUCT_*>_>
          (BASE_STRUCT **param_1,uint param_2,BASE_STRUCT **param_3,
          allocator<BASE_STRUCT_*> *param_4)

{
  unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>(param_1,param_2,param_3);
  return;
}
