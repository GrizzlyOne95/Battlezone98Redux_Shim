/*
 * Entry: 00452270
 * Name: stdext::unchecked_uninitialized_fill_n<Strip_*_*,unsigned_int,Strip_*,std::allocator<Strip_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<Strip_*_*,unsigned_int,Strip_*,std::allocator<Strip_*>_>(Strip * * param_1, uint param_2, Strip * * param_3, allocator<Strip_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_uninitialized_fill_n<Strip_*_*,unsigned_int,Strip_*,std::allocator<Strip_*>_>
          (Strip **param_1,uint param_2,Strip **param_3,allocator<Strip_*> *param_4)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    *param_1 = *param_3;
    param_1 = param_1 + 1;
  }
  return;
}
