/*
 * Entry: 00519327
 * Name: stdext::unchecked_uninitialized_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>(ObjectClassInfo * * param_1, uint param_2, ObjectClassInfo * * param_3, allocator<ObjectClassInfo_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>
          (ObjectClassInfo **param_1,uint param_2,ObjectClassInfo **param_3,
          allocator<ObjectClassInfo_*> *param_4)

{
  unchecked_fill_n<ObjectClassInfo_*_*,unsigned_int,ObjectClassInfo_*>(param_1,param_2,param_3);
  return;
}
