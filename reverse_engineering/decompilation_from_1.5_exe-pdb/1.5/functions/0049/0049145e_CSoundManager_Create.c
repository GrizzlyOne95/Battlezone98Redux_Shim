/*
 * Entry: 0049145e
 * Name: CSoundManager::Create
 * Namespace: CSoundManager
 * Signature: T_HRESULT Create(CSoundManager * this, CSound * * param_1, char * param_2, ulong param_3, _GUID param_4, ulong param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __thiscall
CSoundManager::Create
          (CSoundManager *this,CSound **param_1,char *param_2,ulong param_3,_GUID param_4,
          ulong param_5)

{
  ulong uVar1;
  int iVar2;
  IDirectSoundBuffer **ppIVar3;
  CWaveFile *this_00;
  CSound *pCVar4;
  ulong *puVar5;
  undefined4 local_4c;
  IDirectSoundBuffer **local_48;
  uint local_44;
  ulong local_2c [4];
  tWAVEFORMATEX *local_1c;
  ulong local_18;
  ushort uStack_14;
  ushort uStack_12;
  uchar auStack_10 [4];
  uchar auStack_c [4];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_4c = 0;
  if (this->m_pDS == (IDirectSound8 *)0x0) {
    iVar2 = -0x7ffbfe10;
  }
  else if (((param_2 == (char *)0x0) || (param_1 == (CSound **)0x0)) || (param_5 == 0)) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    ppIVar3 = operator_new__(-(uint)((int)((ulonglong)param_5 * 4 >> 0x20) != 0) |
                             (uint)((ulonglong)param_5 * 4));
    if (ppIVar3 == (IDirectSoundBuffer **)0x0) {
      iVar2 = -0x7ff8fff2;
    }
    else {
      this_00 = operator_new(0x90);
      if (this_00 == (CWaveFile *)0x0) {
        this_00 = (CWaveFile *)0x0;
      }
      else {
        this_00->m_pwfx = (tWAVEFORMATEX *)0x0;
        this_00->m_hmmio = (HMMIO__ *)0x0;
        this_00->m_dwSize = 0;
        this_00->m_bIsReadingFromMemory = false;
      }
      if (this_00 == (CWaveFile *)0x0) {
        iVar2 = -0x7ff8fff2;
      }
      else {
        CWaveFile::Open(this_00,param_2,(tWAVEFORMATEX *)0x0,1);
        uVar1 = this_00->m_dwSize;
        if (uVar1 == 0) {
          iVar2 = -0x7fffbffb;
        }
        else {
          puVar5 = local_2c;
          for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = 0;
            puVar5 = puVar5 + 1;
          }
          local_2c[1] = param_3;
          local_2c[0] = 0x24;
          local_18 = param_4.Data1;
          uStack_14 = param_4.Data2;
          uStack_12 = param_4.Data3;
          auStack_10[0] = param_4.Data4[0];
          auStack_10[1] = param_4.Data4[1];
          auStack_10[2] = param_4.Data4[2];
          auStack_10[3] = param_4.Data4[3];
          auStack_c[0] = param_4.Data4[4];
          auStack_c[1] = param_4.Data4[5];
          auStack_c[2] = param_4.Data4[6];
          auStack_c[3] = param_4.Data4[7];
          local_1c = this_00->m_pwfx;
          local_2c[2] = uVar1;
          iVar2 = (**(code **)((int)*this->m_pDS + 0xc))(this->m_pDS,local_2c,ppIVar3,0);
          if (iVar2 == 0x878000a) {
            local_4c = 0x878000a;
          }
          if (-1 < iVar2) {
            local_44 = 1;
            local_48 = ppIVar3;
            if (1 < param_5) {
              do {
                local_48 = local_48 + 1;
                iVar2 = (**(code **)((int)*this->m_pDS + 0x14))(this->m_pDS,*ppIVar3,local_48);
                if (iVar2 < 0) goto LAB_00491529;
                local_44 = local_44 + 1;
              } while (local_44 < param_5);
            }
            pCVar4 = operator_new(0x14);
            if (pCVar4 == (CSound *)0x0) {
              pCVar4 = (CSound *)0x0;
            }
            else {
              pCVar4 = CSound::CSound(pCVar4,ppIVar3,uVar1,param_5,this_00);
            }
            *param_1 = pCVar4;
            operator_delete(ppIVar3);
            return local_4c;
          }
        }
LAB_00491529:
        CWaveFile::~CWaveFile(this_00);
        operator_delete(this_00);
      }
      operator_delete(ppIVar3);
    }
  }
  return iVar2;
}
