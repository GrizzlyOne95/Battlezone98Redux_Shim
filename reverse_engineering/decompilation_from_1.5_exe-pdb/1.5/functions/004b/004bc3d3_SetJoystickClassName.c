/*
 * Entry: 004bc3d3
 * Name: SetJoystickClassName
 * Namespace: Global
 * Signature: void SetJoystickClassName(_GIDDI_DEVDESC * param_1, tagJOYCAPSA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetJoystickClassName(_GIDDI_DEVDESC *param_1,tagJOYCAPSA *param_2)

{
  uint uVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *_Str;
  
  uVar1 = param_2->wCaps;
  _Str = param_1->long_name;
  pcVar2 = strstr(_Str,"Tracker");
  if (pcVar2 != (char *)0x0) {
    builtin_strncpy(param_1->class_name,"trac",4);
    uVar3._0_1_ = 'k';
    uVar3._1_1_ = 'e';
    uVar3._2_1_ = 'r';
    uVar3._3_1_ = '\0';
LAB_004bc4a9:
    *(undefined4 *)(param_1->class_name + 4) = uVar3;
    return;
  }
  pcVar2 = strstr(_Str,"SideWinder");
  if ((pcVar2 == (char *)0x0) &&
     (((((uVar1 & 1) == 0 || ((uVar1 & 2) == 0)) || ((uVar1 & 0x10) == 0)) ||
      (((uVar1 & 0x20) == 0 || (param_2->wNumButtons != 8)))))) {
    pcVar2 = strstr(_Str,"Flightstick Pro");
    if ((pcVar2 == (char *)0x0) &&
       ((((uVar1 & 1) == 0 || ((uVar1 & 0x10) == 0)) ||
        (((uVar1 & 0x20) == 0 || (param_2->wNumButtons != 4)))))) {
      pcVar2 = strstr(_Str,"Thrustmaster");
      if ((pcVar2 != (char *)0x0) ||
         (((((uVar1 & 2) != 0 && ((uVar1 & 0x10) != 0)) && ((uVar1 & 0x20) != 0)) &&
          (param_2->wNumButtons == 4)))) {
        builtin_strncpy(param_1->class_name,"tmas",4);
        uVar3._0_1_ = 't';
        uVar3._1_1_ = 'e';
        uVar3._2_1_ = 'r';
        uVar3._3_1_ = '\0';
        goto LAB_004bc4a9;
      }
      pcVar2 = "joystick";
    }
    else {
      pcVar2 = "fltstick";
    }
  }
  else {
    pcVar2 = "sidewind";
  }
  *(undefined4 *)param_1->class_name = *(undefined4 *)pcVar2;
  *(undefined4 *)(param_1->class_name + 4) = *(undefined4 *)(pcVar2 + 4);
  param_1->class_name[8] = pcVar2[8];
  return;
}
