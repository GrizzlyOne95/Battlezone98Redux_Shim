/*
 * Entry: 004bddb7
 * Name: giddi_read_channels
 * Namespace: Global
 * Signature: int giddi_read_channels(MOUSE_DATA * param_1, long * param_2, long * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_read_channels(MOUSE_DATA *param_1,long *param_2,long *param_3)

{
  long lVar1;
  long lVar2;
  HWND pHVar3;
  int extraout_EAX;
  long extraout_EAX_00;
  long extraout_EAX_01;
  int extraout_EDX;
  int iVar4;
  int iVar5;
  float fVar6;
  tagPOINT local_14;
  int local_c;
  int local_8;
  
  pHVar3 = GetFocus();
  if (pHVar3 == (HWND)Device.hwndApp) {
    if ((mouseChangeMode != 0) && (clipMouse != 0)) {
      GetWindowScreenCoordinates(&ourWindowRect,Device.Client_Width,Device.Client_Height);
      ClipCursor((RECT *)&ourWindowRect);
      param_1->analog_x = 0;
      giddi_reset(param_1,1);
      giddi_reset(param_1,2);
      giddi_reset(param_1,3);
      mouseChangeMode = 0;
      clipMouse = extraout_EDX;
    }
    if (param_3 != (long *)0x0) {
      *param_3 = discreteSetMap;
      discreteSetMap = discreteSetMap & ~discreteClrMap;
      discreteClrMap = 0;
    }
    if (param_2 != (long *)0x0) {
      fVar6 = TimeStep();
      lVar2 = deltaX;
      lVar1 = deltaY;
      stepTime = fVar6 + stepTime;
      if (0.016666 <= stepTime) {
        local_8 = DELTA_SCALE_FACTOR[(UserProfilePtr->config).mIndex];
        if (UseRawInput != 0) {
          local_c = deltaY * deltaY + deltaX * deltaX;
          _ftol2_sse();
          if (extraout_EAX < 0x180) {
            local_8 = (extraout_EAX + 0x80) * local_8 >> 8;
          }
          else {
            local_8 = local_8 * 2;
          }
        }
        iVar5 = lVar2 * local_8;
        iVar4 = lVar1 * local_8;
        deltaY = iVar4;
        deltaX = iVar5;
        _ftol2_sse();
        param_1->analog_x = param_1->analog_x + iVar5;
        param_1->analog_dx = extraout_EAX_00;
        if (param_1->analog_x < -0x10000) {
          param_1->analog_x = -0x10000;
        }
        else if (0x10000 < param_1->analog_x) {
          param_1->analog_x = 0x10000;
        }
        _ftol2_sse();
        param_1->analog_y = param_1->analog_y + iVar4;
        param_1->analog_dy = extraout_EAX_01;
        if (param_1->analog_y < -0x10000) {
          param_1->analog_y = -0x10000;
        }
        else if (0x10000 < param_1->analog_y) {
          param_1->analog_y = 0x10000;
        }
        *param_2 = param_1->analog_x;
        param_2[1] = param_1->analog_dx;
        param_2[2] = param_1->analog_y;
        param_2[3] = param_1->analog_dy;
        local_14.x = Device.Client_Width >> 1;
        local_14.y = Device.Client_Height >> 1;
        ClientToScreen((HWND)Device.hwndApp,&local_14);
        SetCursorPos(local_14.x,local_14.y);
        deltaX = 0;
        stepTime = 0.0;
        deltaY = 0;
      }
    }
  }
  else {
    stepTime = 0.0;
    if (param_3 != (long *)0x0) {
      *param_3 = 0;
    }
  }
  return 0;
}
