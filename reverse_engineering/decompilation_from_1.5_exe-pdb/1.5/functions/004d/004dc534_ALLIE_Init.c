/*
 * Entry: 004dc534
 * Name: ALLIE_Init
 * Namespace: Global
 * Signature: void ALLIE_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl ALLIE_Init(void)

{
  TEXTINPUT_DEF local_50;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_50.flags = 0;
  local_50.updown_callback = (_func___cdecl_int_void_ptr_ptr_int *)0x0;
  builtin_strncpy(local_50.font,"courier",8);
  local_50.x = 10;
  local_50.y = 300;
  local_50.dx = 0x1e0;
  local_50.color = 0xff;
  local_50.callback = allie_cb;
  allie_entry = TextInput_CreateRegion(&local_50);
  allie_lock = 0;
  allie_show = 1;
  return;
}
