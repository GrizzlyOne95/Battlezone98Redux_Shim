/*
 * Entry: 00476429
 * Name: IForceInit
 * Namespace: Global
 * Signature: Bool IForceInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Bool __cdecl IForceInit(void)

{
  lib = (HINSTANCE__ *)LoadLibraryA("iforce.dll");
  if (lib == (HINSTANCE__ *)0x0) {
    return False;
  }
  pInitStick = (_func___cdecl_Bool_JoystickRecord_ptr *)GetProcAddress((HMODULE)lib,"_InitStick");
  if (pInitStick != (_func___cdecl_Bool_JoystickRecord_ptr *)0x0) {
    pGetStickStatus = (_func___cdecl_Bool_char_ptr *)GetProcAddress((HMODULE)lib,"_GetStickStatus");
    if (pGetStickStatus != (_func___cdecl_Bool_char_ptr *)0x0) {
      pEcho = (_func___cdecl_Bool *)GetProcAddress((HMODULE)lib,"_Echo");
      if (pEcho != (_func___cdecl_Bool *)0x0) {
        pIForceAuthenticate =
             (_func___cdecl_Bool *)GetProcAddress((HMODULE)lib,"_IForceAuthenticate");
        if (pIForceAuthenticate != (_func___cdecl_Bool *)0x0) {
          pGetStickError = (_func___cdecl_int *)GetProcAddress((HMODULE)lib,"_GetStickError");
          if (pGetStickError != (_func___cdecl_int *)0x0) {
            pEnableForces = (_func___cdecl_Bool *)GetProcAddress((HMODULE)lib,"_EnableForces");
            if (pEnableForces != (_func___cdecl_Bool *)0x0) {
              pDisableForces = (_func___cdecl_Bool *)GetProcAddress((HMODULE)lib,"_DisableForces");
              if (pDisableForces != (_func___cdecl_Bool *)0x0) {
                pClearForces = (_func___cdecl_Bool *)GetProcAddress((HMODULE)lib,"_ClearForces");
                if (pClearForces != (_func___cdecl_Bool *)0x0) {
                  pCloseStick = (_func___cdecl_Bool *)GetProcAddress((HMODULE)lib,"_CloseStick");
                  if (pCloseStick != (_func___cdecl_Bool *)0x0) {
                    pSetJoystickPort =
                         (_func___cdecl_void_int *)GetProcAddress((HMODULE)lib,"_SetJoystickPort");
                    if (pSetJoystickPort != (_func___cdecl_void_int *)0x0) {
                      pJolt = (_func___cdecl_Bool_uint_int_uint *)
                              GetProcAddress((HMODULE)lib,"_Jolt");
                      if (pJolt != (_func___cdecl_Bool_uint_int_uint *)0x0) {
                        pButtonReflexJolt =
                             (_func___cdecl_Bool_uint_uint_int_uint_uint *)
                             GetProcAddress((HMODULE)lib,"_ButtonReflexJolt");
                        if (pButtonReflexJolt != (_func___cdecl_Bool_uint_uint_int_uint_uint *)0x0)
                        {
                          pButtonReflexClear =
                               (_func___cdecl_Bool_uint *)
                               GetProcAddress((HMODULE)lib,"_ButtonReflexClear");
                          if (pButtonReflexClear != (_func___cdecl_Bool_uint *)0x0) {
                            pXVibration = (_func___cdecl_Bool_uint_uint_uint *)
                                          GetProcAddress((HMODULE)lib,"_XVibration");
                            if (pXVibration != (_func___cdecl_Bool_uint_uint_uint *)0x0) {
                              pXVibrationClear =
                                   (_func___cdecl_Bool *)
                                   GetProcAddress((HMODULE)lib,"_XVibrationClear");
                              if (pXVibrationClear != (_func___cdecl_Bool *)0x0) {
                                pYVibration = (_func___cdecl_Bool_uint_uint_uint *)
                                              GetProcAddress((HMODULE)lib,"_YVibration");
                                if (pYVibration != (_func___cdecl_Bool_uint_uint_uint *)0x0) {
                                  pYVibrationClear =
                                       (_func___cdecl_Bool *)
                                       GetProcAddress((HMODULE)lib,"_YVibrationClear");
                                  if (pYVibrationClear != (_func___cdecl_Bool *)0x0) {
                                    pBuffeting = (_func___cdecl_Bool_uint *)
                                                 GetProcAddress((HMODULE)lib,"_Buffeting");
                                    if (pBuffeting != (_func___cdecl_Bool_uint *)0x0) {
                                      pBuffetingClear =
                                           (_func___cdecl_Bool *)
                                           GetProcAddress((HMODULE)lib,"_BuffetingClear");
                                      if (pBuffetingClear != (_func___cdecl_Bool *)0x0) {
                                        pVectorForce = (_func___cdecl_Bool_uint_int *)
                                                       GetProcAddress((HMODULE)lib,"_VectorForce");
                                        if (pVectorForce != (_func___cdecl_Bool_uint_int *)0x0) {
                                          pVectorForceClear =
                                               (_func___cdecl_Bool *)
                                               GetProcAddress((HMODULE)lib,"_VectorForceClear");
                                          if (pVectorForceClear != (_func___cdecl_Bool *)0x0) {
                                            pXYVectorForce =
                                                 (_func___cdecl_Bool_int_int *)
                                                 GetProcAddress((HMODULE)lib,"_XYVectorForce");
                                            if (pXYVectorForce != (_func___cdecl_Bool_int_int *)0x0)
                                            {
                                              pEnablePositionReporting =
                                                   (_func___cdecl_Bool_int *)
                                                   GetProcAddress((HMODULE)lib,
                                                                  "_EnablePositionReporting");
                                              if (pEnablePositionReporting !=
                                                  (_func___cdecl_Bool_int *)0x0) {
                                                pDisablePositionReporting =
                                                     (_func___cdecl_Bool *)
                                                     GetProcAddress((HMODULE)lib,
                                                                    "_DisablePositionReporting");
                                                if (pDisablePositionReporting !=
                                                    (_func___cdecl_Bool *)0x0) {
                                                  pGetStickPosition =
                                                       (_func___cdecl_Bool_JoystickPosition_ptr *)
                                                       GetProcAddress((HMODULE)lib,
                                                                      "_GetStickPosition");
                                                  if (pGetStickPosition !=
                                                      (_func___cdecl_Bool_JoystickPosition_ptr *)0x0
                                                     ) {
                                                    pXSpring = (_func___cdecl_Bool_int_uint_uint *)
                                                               GetProcAddress((HMODULE)lib,
                                                                              "_XSpring");
                                                    if (pXSpring !=
                                                        (_func___cdecl_Bool_int_uint_uint *)0x0) {
                                                      pXSpringClear =
                                                           (_func___cdecl_Bool *)
                                                           GetProcAddress((HMODULE)lib,
                                                                          "_XSpringClear");
                                                      if (pXSpringClear != (_func___cdecl_Bool *)0x0
                                                         ) {
                                                        pYSpring = (_func___cdecl_Bool_int_uint_uint
                                                                    *)GetProcAddress((HMODULE)lib,
                                                                                     "_YSpring");
                                                        if (pYSpring !=
                                                            (_func___cdecl_Bool_int_uint_uint *)0x0)
                                                        {
                                                          pYSpringClear =
                                                               (_func___cdecl_Bool *)
                                                               GetProcAddress((HMODULE)lib,
                                                                              "_YSpringClear");
                                                          return (uint)(pYSpringClear !=
                                                                       (_func___cdecl_Bool *)0x0);
                                                        }
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return False;
}
