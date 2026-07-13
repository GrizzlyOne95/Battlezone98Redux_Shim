/*
 * Entry: 0048c27e
 * Name: stdext::unchecked_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>(DistributedObject * * param_1, uint param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>
          (DistributedObject **param_1,uint param_2,DistributedObject **param_3)

{
  std::_Fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
