/*
 * Entry: 0049133c
 * Name: CSound::CSound
 * Namespace: CSound
 * Signature: CSound * CSound(CSound * this, IDirectSoundBuffer * * param_1, ulong param_2, ulong param_3, CWaveFile * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CSound * __thiscall
CSound::CSound(CSound *this,IDirectSoundBuffer **param_1,ulong param_2,ulong param_3,
              CWaveFile *param_4)

{
  IDirectSoundBuffer **ppIVar1;
  uint uVar2;
  
  this->_padding_ = (int)&_vftable_;
  ppIVar1 = operator_new__(-(uint)((int)((ulonglong)param_3 * 4 >> 0x20) != 0) |
                           (uint)((ulonglong)param_3 * 4));
  this->m_apDSBuffer = ppIVar1;
  uVar2 = 0;
  if (param_3 != 0) {
    do {
      this->m_apDSBuffer[uVar2] = param_1[uVar2];
      uVar2 = uVar2 + 1;
    } while (uVar2 < param_3);
  }
  this->m_dwDSBufferSize = param_2;
  this->m_pWaveFile = param_4;
  uVar2 = 0;
  this->m_dwNumBuffers = param_3;
  FillBufferWithSound(this,*this->m_apDSBuffer,false);
  if (param_3 != 0) {
    do {
      (**(code **)((int)*this->m_apDSBuffer[uVar2] + 0x34))(this->m_apDSBuffer[uVar2],0);
      uVar2 = uVar2 + 1;
    } while (uVar2 < param_3);
  }
  return this;
}
