/*
 * Entry: 00571ee9
 * Name: play_anim_sound
 * Namespace: Global
 * Signature: int play_anim_sound(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl play_anim_sound(char *param_1)

{
  if (animSound != (void *)0x0) {
    stop_anim_sound();
  }
  animSound = ShellPlaySound(param_1,100,0,-1);
  return 1;
}
