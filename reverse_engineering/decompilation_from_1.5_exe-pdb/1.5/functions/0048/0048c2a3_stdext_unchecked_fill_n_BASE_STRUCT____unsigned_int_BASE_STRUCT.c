/*
 * Entry: 0048c2a3
 * Name: stdext::unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>(BASE_STRUCT * * param_1, uint param_2, BASE_STRUCT * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>
          (BASE_STRUCT **param_1,uint param_2,BASE_STRUCT **param_3)

{
  std::_Fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
