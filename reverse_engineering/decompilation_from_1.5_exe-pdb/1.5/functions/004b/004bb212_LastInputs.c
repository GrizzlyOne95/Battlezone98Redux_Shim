/*
 * Entry: 004bb212
 * Name: LastInputs
 * Namespace: Global
 * Signature: void LastInputs(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LastInputs(void)

{
  int iVar1;
  _GIDDI_DEVDESC *p_Var2;
  EYE_CONTROLS *pEVar3;
  
  if (num_input_devices != 0) {
    p_Var2 = input_desc + num_input_devices;
    iVar1 = num_input_devices;
    do {
      iVar1 = iVar1 + -1;
      p_Var2 = p_Var2 + -1;
      if (input_enable[iVar1] != 0) {
        (*input_funcs[iVar1]->close)(p_Var2);
      }
    } while (iVar1 != 0);
  }
  pEVar3 = &eye_controls;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pEVar3->track_distance = 0;
    pEVar3 = (EYE_CONTROLS *)&pEVar3->track_distance_plus;
  }
  memset(&user_controls,0,0x34);
  menu_controls.item = 0;
  menu_controls.value = 0;
  menu_controls.item_plus = '\0';
  menu_controls.item_minus = '\0';
  menu_controls.item_reset = '\0';
  menu_controls.value_plus = '\0';
  menu_controls.value_minus = '\0';
  menu_controls.value_reset = '\0';
  menu_controls.enter = '\0';
  menu_controls.abort = '\0';
  num_analog_controls = 0;
  num_analog_sinks = 0;
  num_discrete_controls = 0;
  inputs_enabled = 1;
  memset(invals,0,400);
  kbd_num = 0;
  joy_num = 0;
  inmap_lineno = 0;
  memset(analog_map,0,0xa00);
  memset(analog_sink,0,0x410);
  memset(discrete_map,0,0x5780);
  input_enable[0] = 0;
  input_enable[1] = 0;
  input_enable[2] = 0;
  input_enable[3] = 0;
  num_input_devices = 0;
  input_enable[4] = 0;
  memset(input_names,0,200);
  input_funcs[0] = (_tagGIDDI_DRIVER *)0x0;
  input_funcs[1] = (_tagGIDDI_DRIVER *)0x0;
  input_funcs[2] = (_tagGIDDI_DRIVER *)0x0;
  input_funcs[3] = (_tagGIDDI_DRIVER *)0x0;
  input_funcs[4] = (_tagGIDDI_DRIVER *)0x0;
  memset(input_desc,0,0x244);
  masterGIDDIList[0] = &giddiKeyboard;
  masterGIDDIList[1] = &giddiMouse;
  masterGIDDIList[2] = &giddiJoystick;
  return;
}
