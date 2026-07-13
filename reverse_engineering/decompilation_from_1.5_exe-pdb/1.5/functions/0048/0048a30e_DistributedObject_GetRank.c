/*
 * Entry: 0048a30e
 * Name: DistributedObject::GetRank
 * Namespace: DistributedObject
 * Signature: float GetRank(DistributedObject * this, float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall DistributedObject::GetRank(DistributedObject *this,float param_1,float param_2)

{
  if (param_1 < this->last_send_time) {
    this->last_send_time = param_1;
  }
  return param_1 - this->last_send_time;
}
