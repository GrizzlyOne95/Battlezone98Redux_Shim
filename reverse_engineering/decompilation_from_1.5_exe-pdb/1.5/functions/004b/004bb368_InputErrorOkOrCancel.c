/*
 * Entry: 004bb368
 * Name: InputErrorOkOrCancel
 * Namespace: Global
 * Signature: void InputErrorOkOrCancel(int param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InputErrorOkOrCancel(int param_1,char *param_2,char *param_3)

{
  char *_Format;
  char *pcVar1;
  
  pcVar1 = param_3;
  if (param_1 == 0x6e) {
    _Format = 
    "The input device \"%s\" does not exist or is not configured properly.\nTo eliminate the problem, you should check the Windows Control Panel Joystick settings, or reconfigure your controls in the shell to not use the \"%s\" device.\n\nPush OK to disable this device and continue, or push CANCEL to abort the mission.\n"
    ;
  }
  else if (param_1 == 0x6f) {
    _Format = 
    "The input channel \"%s\" on device \"%s\" does not exist.\nIf you have changed your joystick configuration, you should also reconfigure your controls in the shell.\n\nPush OK to disable this control and continue, or push CANCEL to abort the mission.\n"
    ;
    pcVar1 = param_2;
  }
  else {
    if (param_1 != 0x70) {
      sprintf(messageString,
              "An input device has caused an undefined error. Sorry, no other informationis available.\nPush OK to ignore this error and continue, or push CANCEL to abort the mission.\n"
             );
      goto LAB_004bb3c0;
    }
    _Format = 
    "The input device \"%s\" is not connected properly.\nTo eliminate the problem, you should check that your joystick is plugged in correctly and check the Windows Control Panel settings. Alternatively, you could reconfigure your controls to not use the \"%s\" device.\n\nPush OK to disable this device and continue, or push CANCEL to abort the mission.\n"
    ;
  }
  sprintf(messageString,_Format,pcVar1,param_3);
LAB_004bb3c0:
  DEBUG_systemWarning(messageString);
  return;
}
