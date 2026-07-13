/*
 * Entry: 00490c64
 * Name: CSoundManager::Initialize
 * Namespace: CSoundManager
 * Signature: T_HRESULT Initialize(CSoundManager * this, HWND__ * param_1, ulong param_2, ulong param_3, ulong param_4, ulong param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

undefined4 __thiscall
CSoundManager::Initialize
          (CSoundManager *this,HWND__ *param_1,ulong param_2,ulong param_3,ulong param_4,
          ulong param_5)

{
  IDirectSound8 *pIVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_64;
  byte local_60;
  int local_54;
  uint local_50;
  uint local_4c;
  uint local_44;
  uint local_40;
  uint local_38;
  uint local_34;
  uint local_2c;
  uint local_28;
  uint local_20;
  uint local_1c;
  
  pIVar1 = this->m_pDS;
  if (pIVar1 != (IDirectSound8 *)0x0) {
    (**(code **)((int)*pIVar1 + 8))(pIVar1);
    this->m_pDS = (IDirectSound8 *)0x0;
  }
  iVar2 = _DirectSoundCreate8_12(0,this,0);
  if ((-1 < iVar2) &&
     (iVar2 = (**(code **)((int)*this->m_pDS + 0x18))(this->m_pDS,param_1,param_2), -1 < iVar2)) {
    SetPrimaryBufferFormat(this,param_3,param_4,param_5);
    local_64 = 0x60;
    iVar2 = (**(code **)((int)*this->m_pDS + 0x10))(this->m_pDS,&local_64);
    if (-1 < iVar2) {
      if ((local_60 & 0x20) != 0) {
        UseSWAudioOnly = 1;
      }
      if (local_50 < local_4c) {
        local_4c = local_50;
      }
      if (local_40 <= local_44) {
        local_44 = local_40;
      }
      HWCaps_MaxChannels = local_4c;
      if ((int)local_44 <= (int)local_4c) {
        HWCaps_MaxChannels = local_44;
      }
      if (0x80 < HWCaps_MaxChannels) {
        HWCaps_MaxChannels = 0x80;
      }
      uVar3 = local_38;
      if (local_34 <= local_38) {
        uVar3 = local_34;
      }
      if (local_28 <= local_2c) {
        local_2c = local_28;
      }
      if ((int)uVar3 < (int)local_2c) {
        local_2c = uVar3;
      }
      HWCaps_Max3DChannels = local_2c;
      if (HWCaps_MaxChannels <= (int)local_2c) {
        HWCaps_Max3DChannels = HWCaps_MaxChannels;
      }
      if (HWCaps_Max3DChannels < 2) {
        HWCaps_Max3DChannels = 0;
      }
      if ((UseSWAudioOnly != 0) || ((local_54 == 1 && (HWCaps_MaxChannels < 2)))) {
        HWCaps_Max3DChannels = 0x20;
        HWCaps_MaxChannels = 0x20;
        UseSWAudioOnly = 1;
      }
      if ((local_38 < 2) || (local_34 < 2)) {
        UseDS3DAudio = 0;
        CanDo3DAudio = 0;
      }
      if (((local_20 != 0) || (local_1c != 0)) && (UsedMemory = local_1c, local_20 < local_1c)) {
        UsedMemory = local_20;
      }
      return 0;
    }
  }
  return 0x80004005;
}
