/*
 * Entry: 004905d3
 * Name: CSound::Get3DBufferInterface
 * Namespace: CSound
 * Signature: T_HRESULT Get3DBufferInterface(CSound * this, ulong param_1, IDirectSound3DBuffer * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall
CSound::Get3DBufferInterface(CSound *this,ulong param_1,IDirectSound3DBuffer **param_2)

{
  undefined4 uVar1;
  
  if (this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) {
    uVar1 = 0x800401f0;
  }
  else if (param_1 < this->m_dwNumBuffers) {
    *param_2 = (IDirectSound3DBuffer *)0x0;
    uVar1 = (**(code **)*this->m_apDSBuffer[param_1])
                      (this->m_apDSBuffer[param_1],&IID_IDirectSound3DBuffer,param_2);
  }
  else {
    uVar1 = 0x80070057;
  }
  return uVar1;
}
