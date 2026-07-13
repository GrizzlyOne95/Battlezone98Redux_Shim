/*
 * Entry: 004b14e0
 * Name: CStreamingOggSound::~CStreamingOggSound
 * Namespace: CStreamingOggSound
 * Signature: void ~CStreamingOggSound(CStreamingOggSound * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CStreamingOggSound::~CStreamingOggSound(CStreamingOggSound *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->m_bValid != 0) {
    this->m_bValid = 0;
  }
  CSound::~CSound((CSound *)this);
  return;
}
