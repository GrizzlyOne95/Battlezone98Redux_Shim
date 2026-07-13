/*
 * Entry: 0048c142
 * Name: std::fill<DistributedObject_*_*,DistributedObject_*>
 * Namespace: std
 * Signature: void fill<DistributedObject_*_*,DistributedObject_*>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<DistributedObject_*_*,DistributedObject_*>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
