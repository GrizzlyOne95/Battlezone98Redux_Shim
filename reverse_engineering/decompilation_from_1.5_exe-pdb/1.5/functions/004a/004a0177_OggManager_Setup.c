/*
 * Entry: 004a0177
 * Name: OggManager::Setup
 * Namespace: OggManager
 * Signature: int Setup(char * param_1, uint param_2, bool param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OggManager::Setup(char *param_1,uint param_2,bool param_3)

{
  CStreamingOggSound *pCVar1;
  ov_callbacks oVar2;
  _func___cdecl_uint_void_ptr_uint_uint_void_ptr *p_Var3;
  _func___cdecl_int_void_ptr_long64_int *p_Var4;
  _func___cdecl_int_void_ptr *p_Var5;
  bool *pbVar6;
  int iVar7;
  char *pcVar8;
  int local_8;
  
  p_Var3 = g_Mem_ov_callbacks.read_func;
  local_8 = 0;
  pbVar6 = &gOggStreams[0].m_bPlaying;
  do {
    if (*pbVar6 == false) {
      if ((-1 < local_8) && (local_8 < 8)) {
        gOggStreams[local_8].m_pData = param_1;
        p_Var4 = g_Mem_ov_callbacks.seek_func;
        gOggStreams[local_8].m_DataLen = param_2;
        *(bool *)(local_8 * 0x310 + 0xb09054) = param_3;
        p_Var5 = g_Mem_ov_callbacks.close_func;
        gOggStreams[local_8].m_FilePos = 0;
        oVar2.seek_func = p_Var4;
        oVar2.read_func = p_Var3;
        oVar2.close_func = p_Var5;
        oVar2.tell_func = g_Mem_ov_callbacks.tell_func;
        iVar7 = ov_open_callbacks(gOggStreams + local_8,&gOggStreams[local_8].m_vf,(char *)0x0,0,
                                  oVar2);
        if (iVar7 < 0) {
          pcVar8 = "OggManager::Setup - ov_open_callbacks failed. Requested audio will not play :(";
        }
        else {
          pCVar1 = gOggStreams[local_8].m_pStreamingSound;
          if (pCVar1 != (CStreamingOggSound *)0x0) {
            (**(code **)pCVar1->_padding_)(1);
            gOggStreams[local_8].m_pStreamingSound = (CStreamingOggSound *)0x0;
          }
          iVar7 = CreateStreamingOgg(&gOggStreams[local_8].m_pStreamingSound,
                                     &gOggStreams[local_8].m_vf,0x10188,(_GUID)ZEXT816(0),0x10,
                                     gOggStreams[local_8].m_hNotificationEvent);
          if (-1 < iVar7) {
            gOggStreams[local_8].m_bPlaying = true;
            return local_8;
          }
          pcVar8 = "Couldn\'t create a streaming ogg!\n";
        }
        Trace(pcVar8);
        return -1;
      }
      break;
    }
    local_8 = local_8 + 1;
    pbVar6 = pbVar6 + 0x310;
  } while ((int)pbVar6 < 0xb0a8d5);
  Trace("Max ogg stream count of %d exceeded, requested sound will not play :(");
  return -1;
}
