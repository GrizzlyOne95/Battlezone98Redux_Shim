/*
 * Entry: 0040dce6
 * Name: ArtilleryEnemy::`scalar_deleting_destructor'
 * Namespace: ArtilleryEnemy
 * Signature: void * `scalar_deleting_destructor'(ArtilleryEnemy * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ArtilleryEnemy::_scalar_deleting_destructor_(ArtilleryEnemy *this,uint param_1)

{
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
