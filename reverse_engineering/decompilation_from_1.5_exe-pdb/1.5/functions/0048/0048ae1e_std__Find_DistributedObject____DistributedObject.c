/*
 * Entry: 0048ae1e
 * Name: std::_Find<DistributedObject_*_*,DistributedObject_*>
 * Namespace: std
 * Signature: DistributedObject * * _Find<DistributedObject_*_*,DistributedObject_*>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
std::_Find<DistributedObject_*_*,DistributedObject_*>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3)

{
  if (param_1 != param_2) {
    do {
      if (*param_1 == *param_3) {
        return param_1;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return param_1;
}
