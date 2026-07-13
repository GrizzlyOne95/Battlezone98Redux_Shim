/*
 * Entry: 00491453
 * Name: CStreamingSound::~CStreamingSound
 * Namespace: CStreamingSound
 * Signature: void ~CStreamingSound(CStreamingSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CStreamingSound::~CStreamingSound(CStreamingSound *this)

{
  this->_padding_ = (int)&_vftable_;
  CSound::~CSound((CSound *)this);
  return;
}
