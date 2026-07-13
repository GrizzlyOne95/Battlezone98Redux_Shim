/*
 * Entry: 004ce6c2
 * Name: FlagDisplay::PostRun
 * Namespace: FlagDisplay
 * Signature: void PostRun(FlagDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagDisplay::PostRun(FlagDisplay *this)

{
  if (this->flagTexture[0] != (TEXTURE *)0x0) {
    free(this->flagTexture[0]);
  }
  if (this->flagTexture[1] != (TEXTURE *)0x0) {
    free(this->flagTexture[1]);
  }
  if (this->flagTexture[2] != (TEXTURE *)0x0) {
    free(this->flagTexture[2]);
  }
  this->flagTexture[0] = (TEXTURE *)0x0;
  this->flagTexture[1] = (TEXTURE *)0x0;
  this->flagTexture[2] = (TEXTURE *)0x0;
  return;
}
