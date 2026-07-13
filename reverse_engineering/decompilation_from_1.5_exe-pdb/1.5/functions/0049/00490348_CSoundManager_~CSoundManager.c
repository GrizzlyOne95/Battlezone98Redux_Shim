/*
 * Entry: 00490348
 * Name: CSoundManager::~CSoundManager
 * Namespace: CSoundManager
 * Signature: void ~CSoundManager(CSoundManager * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CSoundManager::~CSoundManager(CSoundManager *this)

{
  IDirectSound8 *pIVar1;
  
  pIVar1 = this->m_pDS;
  if (pIVar1 != (IDirectSound8 *)0x0) {
    (**(code **)((int)*pIVar1 + 8))(pIVar1);
    this->m_pDS = (IDirectSound8 *)0x0;
  }
  return;
}
