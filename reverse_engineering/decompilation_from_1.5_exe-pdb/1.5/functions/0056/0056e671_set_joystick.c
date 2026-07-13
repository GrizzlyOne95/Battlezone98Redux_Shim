/*
 * Entry: 0056e671
 * Name: set_joystick
 * Namespace: Global
 * Signature: int set_joystick(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl set_joystick(void)

{
  char cVar1;
  _JoystickListItem *p_Var2;
  char *pcVar3;
  
  p_Var2 = JoystickList + (UserProfilePtr->config).jIndex;
  pcVar3 = &currentJoystickMap;
  do {
    cVar1 = p_Var2->fileName[0];
    p_Var2 = (_JoystickListItem *)(p_Var2->fileName + 1);
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  return 0;
}
