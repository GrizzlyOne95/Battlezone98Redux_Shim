/*
 * Entry: 004917e6
 * Name: CSoundManager::CreateStreaming
 * Namespace: CSoundManager
 * Signature: T_HRESULT CreateStreaming(CSoundManager * this, CStreamingSound * * param_1, char * param_2, ulong param_3, _GUID param_4, ulong param_5, ulong param_6, void * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall
CSoundManager::CreateStreaming
          (CSoundManager *this,CStreamingSound **param_1,char *param_2,ulong param_3,_GUID param_4,
          ulong param_5,ulong param_6,void *param_7)

{
  undefined4 uVar1;
  void *pvVar2;
  uint uVar3;
  CStreamingSound *pCVar4;
  int iVar5;
  uint *puVar6;
  IDirectSoundBuffer *local_48;
  CWaveFile *local_44;
  int *local_40;
  ulong local_3c;
  ushort uStack_38;
  ushort uStack_36;
  uchar auStack_34 [4];
  uchar auStack_30 [4];
  uint local_2c [2];
  ulong local_24;
  tWAVEFORMATEX *local_1c;
  ulong local_18;
  ushort uStack_14;
  ushort uStack_12;
  uchar auStack_10 [4];
  uchar auStack_c [4];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_3c = param_4.Data1;
  uStack_38 = param_4.Data2;
  uStack_36 = param_4.Data3;
  auStack_34[0] = param_4.Data4[0];
  auStack_34[1] = param_4.Data4[1];
  auStack_34[2] = param_4.Data4[2];
  auStack_34[3] = param_4.Data4[3];
  auStack_30[0] = param_4.Data4[4];
  auStack_30[1] = param_4.Data4[5];
  auStack_30[2] = param_4.Data4[6];
  auStack_30[3] = param_4.Data4[7];
  if (this->m_pDS == (IDirectSound8 *)0x0) {
    uVar1 = 0x800401f0;
  }
  else if (((param_2 == (char *)0x0) || (param_1 == (CStreamingSound **)0x0)) ||
          (param_7 == (void *)0x0)) {
    uVar1 = 0x80070057;
  }
  else {
    local_48 = (IDirectSoundBuffer *)0x0;
    local_40 = (int *)0x0;
    local_44 = operator_new(0x90);
    if (local_44 == (CWaveFile *)0x0) {
      local_44 = (CWaveFile *)0x0;
    }
    else {
      local_44->m_pwfx = (tWAVEFORMATEX *)0x0;
      local_44->m_hmmio = (HMMIO__ *)0x0;
      local_44->m_dwSize = 0;
      local_44->m_bIsReadingFromMemory = false;
    }
    CWaveFile::Open(local_44,param_2,(tWAVEFORMATEX *)0x0,1);
    puVar6 = local_2c;
    for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    local_2c[1] = param_3 | 0x10100;
    local_2c[0] = 0x24;
    local_18 = local_3c;
    uStack_14 = uStack_38;
    uStack_12 = uStack_36;
    auStack_10[0] = auStack_34[0];
    auStack_10[1] = auStack_34[1];
    auStack_10[2] = auStack_34[2];
    auStack_10[3] = auStack_34[3];
    auStack_c[0] = auStack_30[0];
    auStack_c[1] = auStack_30[1];
    auStack_c[2] = auStack_30[2];
    auStack_c[3] = auStack_30[3];
    local_1c = local_44->m_pwfx;
    local_24 = param_5 * param_6;
    iVar5 = (**(code **)((int)*this->m_pDS + 0xc))(this->m_pDS,local_2c,&local_48,0);
    if ((-1 < iVar5) &&
       (iVar5 = (**(code **)*local_48)(local_48,&IID_IDirectSoundNotify,&local_40), -1 < iVar5)) {
      pvVar2 = operator_new__(-(uint)((int)((ulonglong)param_5 * 8 >> 0x20) != 0) |
                              (uint)((ulonglong)param_5 * 8));
      uVar3 = 0;
      if (pvVar2 == (void *)0x0) {
        return 0x8007000e;
      }
      if (param_5 != 0) {
        iVar5 = param_6 - 1;
        do {
          *(int *)((int)pvVar2 + uVar3 * 8) = iVar5;
          *(void **)((int)pvVar2 + uVar3 * 8 + 4) = param_7;
          uVar3 = uVar3 + 1;
          iVar5 = iVar5 + param_6;
        } while (uVar3 < param_5);
      }
      iVar5 = (**(code **)(*local_40 + 0xc))(local_40,param_5,pvVar2);
      if (-1 < iVar5) {
        if (local_40 != (int *)0x0) {
          (**(code **)(*local_40 + 8))(local_40);
          local_40 = (int *)0x0;
        }
        operator_delete(pvVar2);
        pCVar4 = operator_new(0x28);
        if (pCVar4 == (CStreamingSound *)0x0) {
          pCVar4 = (CStreamingSound *)0x0;
        }
        else {
          pCVar4 = CStreamingSound::CStreamingSound
                             (pCVar4,local_48,param_5 * param_6,local_44,param_6);
        }
        *param_1 = pCVar4;
        return 0;
      }
      if (local_40 != (int *)0x0) {
        (**(code **)(*local_40 + 8))(local_40);
        local_40 = (int *)0x0;
      }
      operator_delete(pvVar2);
    }
    uVar1 = 0x80004005;
  }
  return uVar1;
}
