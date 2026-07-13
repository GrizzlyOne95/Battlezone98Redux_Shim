/*
 * Entry: 0048ad8b
 * Name: std::_Fill<DistributedObject_*_*,DistributedObject_*>
 * Namespace: std
 * Signature: void _Fill<DistributedObject_*_*,DistributedObject_*>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<DistributedObject_*_*,DistributedObject_*>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
