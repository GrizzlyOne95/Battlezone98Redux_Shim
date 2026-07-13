/*
 * Entry: 004a051c
 * Name: OggManager::Release
 * Namespace: OggManager
 * Signature: bool Release(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl OggManager::Release(int param_1)

{
  CStreamingOggSound *pCVar1;
  
  if ((uint)param_1 < 8) {
    if (gOggStreams[param_1].m_bPlaying != false) {
      EnterCriticalSection((LPCRITICAL_SECTION)&gOggStreams[param_1].m_OggMutex);
      pCVar1 = gOggStreams[param_1].m_pStreamingSound;
      if (pCVar1 == (CStreamingOggSound *)0x0) {
        Trace(
             "UHOH - OggManager::Release index %d has NO pStreamingSound but is playing. Attempting to fix\n"
             );
      }
      else {
        (**(code **)pCVar1->_padding_)(1);
        gOggStreams[param_1].m_pStreamingSound = (CStreamingOggSound *)0x0;
      }
      ov_clear(&gOggStreams[param_1].m_vf);
      gOggStreams[param_1].m_bPlaying = false;
      memset(&gOggStreams[param_1].m_vf,0,0x2d0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&gOggStreams[param_1].m_OggMutex);
      return true;
    }
    Trace("OggManager::Release index %d is not playing");
  }
  return false;
}
