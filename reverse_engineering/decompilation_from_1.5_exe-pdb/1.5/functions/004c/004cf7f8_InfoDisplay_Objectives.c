/*
 * Entry: 004cf7f8
 * Name: InfoDisplay_Objectives
 * Namespace: Global
 * Signature: void InfoDisplay_Objectives(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InfoDisplay_Objectives(void)

{
  oOn = !oOn;
  if (oOn) {
    oTimes = oTimes + '\x01';
  }
  InfoDisplay::ToggleObjectives(&infoDisplay);
  return;
}
