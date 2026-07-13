/*
 * Entry: 004b1595
 * Name: CStreamingOggSound::FillBufferWithSound
 * Namespace: CStreamingOggSound
 * Signature: T_HRESULT FillBufferWithSound(CStreamingOggSound * this, IDirectSoundBuffer * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall
CStreamingOggSound::FillBufferWithSound
          (CStreamingOggSound *this,IDirectSoundBuffer *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  void *local_c;
  ulong local_8;
  
  local_c = (void *)0x0;
  local_8 = 0;
  if (param_1 == (IDirectSoundBuffer *)0x0) {
    uVar1 = 0x800401f0;
  }
  else {
    iVar2 = CSound::RestoreBuffer((CSound *)this,param_1,(bool *)0x0);
    if (-1 < iVar2) {
      iVar2 = (**(code **)((int)*param_1 + 0x2c))(param_1,0,this->_padding_,&local_c,&local_8,0,0,0)
      ;
      if (-1 < iVar2) {
        DecodeToBuffer(this,local_c,local_8,0);
        (**(code **)((int)*param_1 + 0x4c))(param_1,local_c,local_8,0,0);
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}
