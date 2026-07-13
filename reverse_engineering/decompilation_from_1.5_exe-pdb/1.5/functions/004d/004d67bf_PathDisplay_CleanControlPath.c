/*
 * Entry: 004d67bf
 * Name: PathDisplay::CleanControlPath
 * Namespace: PathDisplay
 * Signature: void CleanControlPath(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::CleanControlPath(PathDisplay *this)

{
  if (this->editSelect != 0) {
    SetEditPath(this,(AiPath *)0x0);
  }
  return;
}
