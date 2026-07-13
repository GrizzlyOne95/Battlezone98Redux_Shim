/*
 * Entry: 004dc38c
 * Name: ALLIE_InputMessage
 * Namespace: Global
 * Signature: void ALLIE_InputMessage(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl ALLIE_InputMessage(int param_1)

{
  char local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (allie_lock == 0) {
    A = param_1;
    if (param_1 == 0) {
      builtin_strncpy(local_30,"Unally with: ",0xe);
    }
    else {
      builtin_strncpy(local_30,"Ally with: ",0xc);
    }
    TextInput_SetPrompt(allie_entry,local_30);
    TextInput_SetString(allie_entry,"");
    TextInput_ShowRegion(allie_entry,1);
    TextInput_AllowInput(allie_entry,1);
  }
  return;
}
