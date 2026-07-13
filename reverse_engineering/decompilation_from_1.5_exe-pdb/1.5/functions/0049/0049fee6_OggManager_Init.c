/*
 * Entry: 0049fee6
 * Name: OggManager::Init
 * Namespace: OggManager
 * Signature: void Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OggManager::Init(void)

{
  HANDLE pvVar1;
  OggStreamInfo *_ArgList;
  
  _ArgList = gOggStreams;
  do {
    InitializeCriticalSection((LPCRITICAL_SECTION)&_ArgList->m_OggMutex);
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
    _ArgList->m_hNotificationEvent = pvVar1;
    pvVar1 = (HANDLE)_beginthreadex((void *)0x0,0,OggNotificationProc,_ArgList,0,
                                    &_ArgList->m_dwNotifyThreadID);
    _ArgList->m_hNotifyThread = pvVar1;
    SetThreadPriority(pvVar1,1);
    _ArgList = _ArgList + 1;
  } while ((int)_ArgList < 0xb0a8c8);
  return;
}
