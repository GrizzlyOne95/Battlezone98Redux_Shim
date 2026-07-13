/*
 * Entry: 00490db2
 * Name: CSound::FillBufferWithSound
 * Namespace: CSound
 * Signature: T_HRESULT FillBufferWithSound(CSound * this, IDirectSoundBuffer * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall
CSound::FillBufferWithSound(CSound *this,IDirectSoundBuffer *param_1,bool param_2)

{
  ushort uVar1;
  int iVar2;
  ulong uVar3;
  uchar *puVar4;
  ulong local_10;
  uchar *local_c;
  ulong local_8;
  
  local_c = (uchar *)0x0;
  local_8 = 0;
  local_10 = 0;
  if (param_1 == (IDirectSoundBuffer *)0x0) {
    return 0x800401f0;
  }
  iVar2 = RestoreBuffer(this,param_1,(bool *)0x0);
  if (iVar2 < 0) {
    return 0x80004005;
  }
  if (this->m_pWaveFile == (CWaveFile *)0x0) {
    return 0;
  }
  iVar2 = (**(code **)((int)*param_1 + 0x2c))
                    (param_1,0,this->m_dwDSBufferSize,&local_c,&local_8,0,0,0);
  if (iVar2 < 0) {
    return 0x80004005;
  }
  CWaveFile::ResetFile(this->m_pWaveFile);
  iVar2 = CWaveFile::Read(this->m_pWaveFile,local_c,local_8,&local_10);
  if (iVar2 < 0) {
    return 0x80004005;
  }
  if (local_10 == 0) {
    uVar1 = this->m_pWaveFile->m_pwfx->wBitsPerSample;
    puVar4 = local_c;
    uVar3 = local_8;
  }
  else {
    if (local_8 <= local_10) goto LAB_00490ec3;
    uVar3 = local_10;
    if (param_2) {
      do {
        iVar2 = CWaveFile::ResetFile(this->m_pWaveFile);
        if (iVar2 < 0) {
          return 0x80004005;
        }
        iVar2 = CWaveFile::Read(this->m_pWaveFile,local_c + uVar3,local_8 - uVar3,&local_10);
        if (iVar2 < 0) {
          return 0x80004005;
        }
        uVar3 = uVar3 + local_10;
      } while (uVar3 < local_8);
      goto LAB_00490ec3;
    }
    uVar3 = local_8 - local_10;
    uVar1 = this->m_pWaveFile->m_pwfx->wBitsPerSample;
    puVar4 = local_c + local_10;
  }
  memset(puVar4,(uVar1 != 8) - 1U & 0x80,uVar3);
LAB_00490ec3:
  (**(code **)((int)*param_1 + 0x4c))(param_1,local_c,local_8,0,0);
  return 0;
}
