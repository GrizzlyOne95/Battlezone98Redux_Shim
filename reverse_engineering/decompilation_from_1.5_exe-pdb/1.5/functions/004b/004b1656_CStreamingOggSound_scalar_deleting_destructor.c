/*
 * Entry: 004b1656
 * Name: CStreamingOggSound::`scalar_deleting_destructor'
 * Namespace: CStreamingOggSound
 * Signature: void * `scalar_deleting_destructor'(CStreamingOggSound * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
CStreamingOggSound::_scalar_deleting_destructor_(CStreamingOggSound *this,uint param_1)

{
  ~CStreamingOggSound(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
