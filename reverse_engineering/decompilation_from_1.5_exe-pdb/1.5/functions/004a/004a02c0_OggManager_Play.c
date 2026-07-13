/*
 * Entry: 004a02c0
 * Name: OggManager::Play
 * Namespace: OggManager
 * Signature: bool Play(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl OggManager::Play(int param_1)

{
  _RTL_CRITICAL_SECTION *lpCriticalSection;
  int iVar1;
  IDirectSoundBuffer *pIVar2;
  char *pcVar3;
  
  if ((uint)param_1 < 8) {
    if (gOggStreams[param_1].m_bPlaying == false) {
      pcVar3 = "OggManager::Play index %d is not playing";
    }
    else if (gOggStreams[param_1].m_pStreamingSound == (CStreamingOggSound *)0x0) {
      pcVar3 = "OggManager::Play index %d has no pStreamingSound";
    }
    else {
      lpCriticalSection = &gOggStreams[param_1].m_OggMutex;
      EnterCriticalSection((LPCRITICAL_SECTION)lpCriticalSection);
      iVar1 = CStreamingOggSound::Reset(gOggStreams[param_1].m_pStreamingSound);
      if (iVar1 < 0) {
        LeaveCriticalSection((LPCRITICAL_SECTION)lpCriticalSection);
        pcVar3 = "OggManager::Play index %d Reset() failed";
      }
      else {
        pIVar2 = CSound::GetBuffer((CSound *)gOggStreams[param_1].m_pStreamingSound,0);
        iVar1 = CStreamingOggSound::FillBufferWithSound
                          (gOggStreams[param_1].m_pStreamingSound,pIVar2,
                           (uint)gOggStreams[param_1].m_bPlayLooped);
        if (iVar1 < 0) {
          LeaveCriticalSection((LPCRITICAL_SECTION)lpCriticalSection);
          pcVar3 = "OggManager::Play index %d FillBufferWithSound() failed";
        }
        else {
          iVar1 = CSound::Play((CSound *)gOggStreams[param_1].m_pStreamingSound,0,1);
          if (-1 < iVar1) {
            LeaveCriticalSection((LPCRITICAL_SECTION)lpCriticalSection);
            return true;
          }
          LeaveCriticalSection((LPCRITICAL_SECTION)lpCriticalSection);
          pcVar3 = "OggManager::Play index %d Play() failed";
        }
      }
    }
    Trace(pcVar3);
  }
  return false;
}
