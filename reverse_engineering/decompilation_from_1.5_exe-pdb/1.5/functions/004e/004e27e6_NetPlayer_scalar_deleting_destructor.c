/*
 * Entry: 004e27e6
 * Name: NetPlayer::`scalar_deleting_destructor'
 * Namespace: NetPlayer
 * Signature: void * `scalar_deleting_destructor'(NetPlayer * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall NetPlayer::_scalar_deleting_destructor_(NetPlayer *this,uint param_1)

{
  ~NetPlayer(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
