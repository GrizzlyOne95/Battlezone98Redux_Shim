
void FUN_00621820(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (param_1 == 0x6e) {
    sprintf(&DAT_02a13ee0,
            "The input device \"%s\" does not exist or is not configured properly.\nTo eliminate the problem, you should check the Windows Control Panel Joystick settings, or reconfigure your controls in the shell to not use the \"%s\" device.\n\nPush OK to disable this device and continue, or push CANCEL to abort the mission.\n"
            ,param_3,param_3);
  }
  else if (param_1 == 0x6f) {
    sprintf(&DAT_02a13ee0,
            "The input channel \"%s\" on device \"%s\" does not exist.\nIf you have changed your joystick configuration, you should also reconfigure your controls in the shell.\n\nPush OK to disable this control and continue, or push CANCEL to abort the mission.\n"
            ,param_2,param_3);
  }
  else if (param_1 == 0x70) {
    sprintf(&DAT_02a13ee0,
            "The input device \"%s\" is not connected properly.\nTo eliminate the problem, you should check that your joystick is plugged in correctly and check the Windows Control Panel settings. Alternatively, you could reconfigure your controls to not use the \"%s\" device.\n\nPush OK to disable this device and continue, or push CANCEL to abort the mission.\n"
            ,param_3,param_3);
  }
  else {
    sprintf(&DAT_02a13ee0,
            "An input device has caused an undefined error. Sorry, no other informationis available.\nPush OK to ignore this error and continue, or push CANCEL to abort the mission.\n"
           );
  }
  FUN_007d6c70(&DAT_00879854,&DAT_02a13ee0);
  return;
}

