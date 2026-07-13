/*
 * Entry: 004bc18f
 * Name: joystick_scale
 * Namespace: Global
 * Signature: long joystick_scale(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl joystick_scale(long param_1,long param_2,long param_3)

{
  int in_EAX;
  int in_ECX;
  
  return joystickRemap[(UserProfilePtr->config).jSensitivity]
         [((in_EAX - param_1) * 0xfe) / (in_ECX - param_1)];
}
