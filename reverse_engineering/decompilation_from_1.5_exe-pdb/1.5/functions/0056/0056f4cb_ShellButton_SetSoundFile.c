/*
 * Entry: 0056f4cb
 * Name: ShellButton::SetSoundFile
 * Namespace: ShellButton
 * Signature: int SetSoundFile(ShellButton * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::SetSoundFile(ShellButton *this,char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0x90 - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[(int)this + iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  iVar2 = 0xd0 - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[(int)this + iVar2] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  this->nSoundEffect = 1;
  return 1;
}
