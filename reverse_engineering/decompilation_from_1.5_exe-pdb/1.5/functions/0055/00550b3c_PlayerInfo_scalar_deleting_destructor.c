/*
 * Entry: 00550b3c
 * Name: PlayerInfo::`scalar_deleting_destructor'
 * Namespace: PlayerInfo
 * Signature: void * `scalar_deleting_destructor'(PlayerInfo * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PlayerInfo::_scalar_deleting_destructor_(PlayerInfo *this,uint param_1)

{
  ~PlayerInfo(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
