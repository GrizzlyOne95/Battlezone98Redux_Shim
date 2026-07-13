/*
 * Entry: 00490edd
 * Name: CSound::Play
 * Namespace: CSound
 * Signature: T_HRESULT Play(CSound * this, ulong param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall CSound::Play(CSound *this,ulong param_1,ulong param_2)

{
  IDirectSoundBuffer *pIVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uStack_8;
  
  uStack_8 = (uint)this & 0xffffff;
  if (this->m_apDSBuffer == (IDirectSoundBuffer **)0x0) {
    return 0x800401f0;
  }
  pIVar1 = GetFreeBuffer(this);
  if ((pIVar1 == (IDirectSoundBuffer *)0x0) ||
     (iVar2 = RestoreBuffer(this,pIVar1,(bool *)((int)&uStack_8 + 3)), iVar2 < 0)) {
LAB_00490f24:
    uVar3 = 0x80004005;
  }
  else {
    if (uStack_8._3_1_ != '\0') {
      iVar2 = FillBufferWithSound(this,pIVar1,false);
      if (iVar2 < 0) goto LAB_00490f24;
      Reset(this);
    }
    uVar3 = (**(code **)((int)*pIVar1 + 0x30))(pIVar1,0,param_1,param_2);
  }
  return uVar3;
}
