/*
 * Entry: 00571049
 * Name: stop_anim_sound
 * Namespace: Global
 * Signature: int stop_anim_sound(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl stop_anim_sound(void)

{
  int iVar1;
  
  if (animSound == (void *)0x0) {
    return 0;
  }
  iVar1 = ShellIsGASSoundPlaying(animSound);
  if (iVar1 != 0) {
    ShellStopGASEvent(animSound);
  }
  animSound = (void *)0x0;
  return 1;
}
