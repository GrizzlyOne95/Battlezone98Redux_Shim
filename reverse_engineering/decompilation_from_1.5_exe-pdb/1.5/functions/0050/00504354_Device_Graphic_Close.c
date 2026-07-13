/*
 * Entry: 00504354
 * Name: Device_Graphic_Close
 * Namespace: Global
 * Signature: void Device_Graphic_Close(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Device_Graphic_Close(VIDEO_DEVICE *param_1)

{
  _func___cdecl_void_void_ptr *p_Var1;
  
  if ((param_1 != (VIDEO_DEVICE *)0x0) &&
     (p_Var1 = (param_1->VideoMode).close, p_Var1 != (_func___cdecl_void_void_ptr *)0x0)) {
    (*p_Var1)(param_1);
  }
  return;
}
