/*
 * Entry: 00491320
 * Name: CWaveFile::`scalar_deleting_destructor'
 * Namespace: CWaveFile
 * Signature: void * `scalar_deleting_destructor'(CWaveFile * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CWaveFile::_scalar_deleting_destructor_(CWaveFile *this,uint param_1)

{
  ~CWaveFile(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
