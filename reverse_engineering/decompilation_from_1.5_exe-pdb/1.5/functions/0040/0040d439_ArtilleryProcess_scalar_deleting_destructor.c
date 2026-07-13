/*
 * Entry: 0040d439
 * Name: ArtilleryProcess::`scalar_deleting_destructor'
 * Namespace: ArtilleryProcess
 * Signature: void * `scalar_deleting_destructor'(ArtilleryProcess * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ArtilleryProcess::_scalar_deleting_destructor_(ArtilleryProcess *this,uint param_1)

{
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
