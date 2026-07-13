/*
 * Entry: 0049161d
 * Name: CSoundManager::CreateFromMemory
 * Namespace: CSoundManager
 * Signature: T_HRESULT CreateFromMemory(CSoundManager * this, char * param_1, CSound * * param_2, uchar * param_3, ulong param_4, tWAVEFORMATEX * param_5, ulong param_6, _GUID param_7, ulong param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

DWORD __thiscall
CSoundManager::CreateFromMemory
          (CSoundManager *this,char *param_1,CSound **param_2,uchar *param_3,ulong param_4,
          tWAVEFORMATEX *param_5,ulong param_6,_GUID param_7,ulong param_8)

{
  DWORD dwMessageId;
  DWORD DVar1;
  CSound *pCVar2;
  int iVar3;
  ulong *puVar4;
  IDirectSoundBuffer **ppIVar5;
  CSound **local_4c;
  CWaveFile *local_48;
  IDirectSoundBuffer **local_44;
  tWAVEFORMATEX *local_40;
  ulong local_3c;
  ushort uStack_38;
  ushort uStack_36;
  uchar auStack_34 [4];
  uchar auStack_30 [4];
  ulong local_2c [5];
  ulong local_18;
  ushort uStack_14;
  ushort uStack_12;
  uchar auStack_10 [4];
  uchar auStack_c [4];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_3c = param_7.Data1;
  uStack_38 = param_7.Data2;
  uStack_36 = param_7.Data3;
  auStack_34[0] = param_7.Data4[0];
  auStack_34[1] = param_7.Data4[1];
  auStack_34[2] = param_7.Data4[2];
  auStack_34[3] = param_7.Data4[3];
  local_4c = param_2;
  local_40 = param_5;
  auStack_30[0] = param_7.Data4[4];
  auStack_30[1] = param_7.Data4[5];
  auStack_30[2] = param_7.Data4[6];
  auStack_30[3] = param_7.Data4[7];
  if (this->m_pDS == (IDirectSound8 *)0x0) {
    dwMessageId = 0x800401f0;
  }
  else if (((param_3 == (uchar *)0x0) || (param_2 == (CSound **)0x0)) || (param_8 == 0)) {
    dwMessageId = 0x80070057;
  }
  else {
    local_44 = operator_new__(-(uint)((int)((ulonglong)param_8 * 4 >> 0x20) != 0) |
                              (uint)((ulonglong)param_8 * 4));
    if (local_44 == (IDirectSoundBuffer **)0x0) {
      dwMessageId = 0x8007000e;
    }
    else {
      local_48 = operator_new(0x90);
      if (local_48 == (CWaveFile *)0x0) {
        local_48 = (CWaveFile *)0x0;
      }
      else {
        local_48->m_pwfx = (tWAVEFORMATEX *)0x0;
        local_48->m_hmmio = (HMMIO__ *)0x0;
        local_48->m_dwSize = 0;
        local_48->m_bIsReadingFromMemory = false;
      }
      if (local_48 == (CWaveFile *)0x0) {
        dwMessageId = 0x8007000e;
      }
      else {
        CWaveFile::OpenFromMemory(local_48,param_3,param_4,local_40,1);
        ppIVar5 = local_44;
        puVar4 = local_2c;
        for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        local_2c[2] = param_4;
        local_2c[1] = param_6;
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
        dwMessageId = (**(code **)((int)*this->m_pDS + 0xc))(this->m_pDS,local_2c,local_44,0);
        if (-1 < (int)dwMessageId) {
          local_40 = (tWAVEFORMATEX *)0x1;
          if (1 < param_8) {
            do {
              ppIVar5 = ppIVar5 + 1;
              dwMessageId = (**(code **)((int)*this->m_pDS + 0x14))(this->m_pDS,*local_44,ppIVar5);
              if ((int)dwMessageId < 0) goto LAB_004916cc;
              local_40 = (tWAVEFORMATEX *)((int)&local_40->wFormatTag + 1);
            } while (local_40 < param_8);
          }
          pCVar2 = operator_new(0x14);
          if (pCVar2 == (CSound *)0x0) {
            pCVar2 = (CSound *)0x0;
          }
          else {
            pCVar2 = CSound::CSound(pCVar2,local_44,param_4,param_8,local_48);
          }
          *local_4c = pCVar2;
          operator_delete(local_44);
          return 0;
        }
        DVar1 = GetTickCount();
        if (300000 < DVar1 - LastAudioComplaintTicks) {
          LastAudioComplaintTicks = DVar1;
          FormatMessageA(0x1300,(LPCVOID)0x0,dwMessageId,0x400,(LPSTR)&local_4c,0,(va_list *)0x0);
        }
      }
LAB_004916cc:
      operator_delete(local_44);
    }
  }
  return dwMessageId;
}
