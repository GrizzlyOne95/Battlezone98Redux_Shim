/*
 * Entry: 0049ff3d
 * Name: OggManager::Cleanup
 * Namespace: OggManager
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OggManager::Cleanup(void)

{
  LPCRITICAL_SECTION lpCriticalSection;
  
  lpCriticalSection = (LPCRITICAL_SECTION)&gOggStreams[0].m_OggMutex;
  do {
    CloseHandle(lpCriticalSection[-0x20].OwningThread);
    DeleteCriticalSection(lpCriticalSection);
    lpCriticalSection = (LPCRITICAL_SECTION)&lpCriticalSection[0x20].LockSemaphore;
  } while ((int)lpCriticalSection < 0xb0abbc);
  return;
}
