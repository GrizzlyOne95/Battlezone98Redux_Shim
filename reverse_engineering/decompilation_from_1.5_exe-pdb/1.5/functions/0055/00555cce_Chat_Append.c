/*
 * Entry: 00555cce
 * Name: Chat::Append
 * Namespace: Chat
 * Signature: void Append(Chat * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::Append(Chat *this,char *param_1)

{
  char *in_stack_00000008;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,in_stack_00000008,&stack0x0000000c);
  if (times_on != 0) {
    AppendTime((Chat *)param_1,ChatColor[0].Value);
  }
  AppendNoNewLine((Chat *)param_1,ChatColor[0].Value,local_408);
  param_1[4] = '\x01';
  return;
}
