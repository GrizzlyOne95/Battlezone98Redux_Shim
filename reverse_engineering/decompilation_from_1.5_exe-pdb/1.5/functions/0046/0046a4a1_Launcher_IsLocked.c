/*
 * Entry: 0046a4a1
 * Name: Launcher::IsLocked
 * Namespace: Launcher
 * Signature: bool IsLocked(Launcher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Launcher::IsLocked(Launcher *this)

{
  return this->lockTarget != 0;
}
