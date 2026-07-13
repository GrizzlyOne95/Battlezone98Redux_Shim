/*
 * Entry: 0049ff66
 * Name: CreateStreamingOgg
 * Namespace: Global
 * Signature: T_HRESULT CreateStreamingOgg(CStreamingOggSound * * param_1, OggVorbis_File * param_2, ulong param_3, _GUID param_4, ulong param_5, void * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
CreateStreamingOgg(CStreamingOggSound **param_1,OggVorbis_File *param_2,ulong param_3,_GUID param_4,
                  ulong param_5,void *param_6)

{
  ulong uVar1;
  vorbis_info *pvVar2;
  void *pvVar3;
  uint uVar4;
  CStreamingOggSound *pCVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ulong uVar9;
  uint *puVar10;
  IDirectSoundBuffer *local_44;
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
  if ((param_1 == (CStreamingOggSound **)0x0) || (param_6 == (void *)0x0)) {
    iVar7 = -0x7ff8ffa9;
  }
  else {
    local_44 = (IDirectSoundBuffer *)0x0;
    local_40 = (int *)0x0;
    pvVar2 = ov_info(param_2,-1);
    uVar4 = pvVar2->channels;
    uVar1 = pvVar2->rate;
    uVar6 = (uVar4 << 4) >> 3;
    uVar8 = uVar6 * uVar1 * 3 >> 4;
    puVar10 = local_2c;
    for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    local_2c[1] = param_3 | 0x10100;
    local_2c[0] = 0x24;
    mOutWaveFormat.wFormatTag = 1;
    mOutWaveFormat.wBitsPerSample = 0x10;
    uVar9 = uVar8 - uVar8 % uVar6;
    local_18 = local_3c;
    uStack_14 = uStack_38;
    uStack_12 = uStack_36;
    mOutWaveFormat.cbSize = 0;
    auStack_10[0] = auStack_34[0];
    auStack_10[1] = auStack_34[1];
    auStack_10[2] = auStack_34[2];
    auStack_10[3] = auStack_34[3];
    mOutWaveFormat.nChannels = (ushort)uVar4;
    auStack_c[0] = auStack_30[0];
    auStack_c[1] = auStack_30[1];
    auStack_c[2] = auStack_30[2];
    auStack_c[3] = auStack_30[3];
    iVar7 = (uVar4 & 0xffff) * 0x10;
    mOutWaveFormat.nBlockAlign = (ushort)(iVar7 >> 3);
    mOutWaveFormat.nAvgBytesPerSec = iVar7 * uVar1 >> 3;
    local_1c = &mOutWaveFormat;
    mOutWaveFormat.nSamplesPerSec = uVar1;
    local_24 = uVar9 * param_5;
    iVar7 = (**(code **)((int)*GM->DSHandle + 0xc))(GM->DSHandle,local_2c,&local_44,0);
    if (iVar7 < 0) {
      Trace("Couldn\'t CreateSoundBuffer(). hr = %08X (%d)\n");
    }
    else {
      (**(code **)*local_44)(local_44,&IID_IDirectSoundNotify,&local_40);
      pvVar3 = operator_new__(-(uint)((int)((ulonglong)param_5 * 8 >> 0x20) != 0) |
                              (uint)((ulonglong)param_5 * 8));
      uVar4 = 0;
      if (pvVar3 == (void *)0x0) {
        iVar7 = -0x7ff8fff2;
      }
      else {
        if (param_5 != 0) {
          iVar7 = uVar9 - 1;
          do {
            *(int *)((int)pvVar3 + uVar4 * 8) = iVar7;
            *(void **)((int)pvVar3 + uVar4 * 8 + 4) = param_6;
            uVar4 = uVar4 + 1;
            iVar7 = iVar7 + uVar9;
          } while (uVar4 < param_5);
        }
        iVar7 = (**(code **)(*local_40 + 0xc))(local_40,param_5,pvVar3);
        if (iVar7 < 0) {
          if (local_40 != (int *)0x0) {
            (**(code **)(*local_40 + 8))(local_40);
            local_40 = (int *)0x0;
          }
          operator_delete__(pvVar3);
        }
        else {
          if (local_40 != (int *)0x0) {
            (**(code **)(*local_40 + 8))(local_40);
            local_40 = (int *)0x0;
          }
          operator_delete__(pvVar3);
          pCVar5 = operator_new(0x38);
          if (pCVar5 == (CStreamingOggSound *)0x0) {
            pCVar5 = (CStreamingOggSound *)0x0;
          }
          else {
            pCVar5 = CStreamingOggSound::CStreamingOggSound
                               (pCVar5,local_44,uVar9 * param_5,param_2,uVar9);
          }
          *param_1 = pCVar5;
          (**(code **)((int)*local_44 + 0x44))(local_44,uVar1);
          iVar7 = 0;
        }
      }
    }
  }
  return iVar7;
}
