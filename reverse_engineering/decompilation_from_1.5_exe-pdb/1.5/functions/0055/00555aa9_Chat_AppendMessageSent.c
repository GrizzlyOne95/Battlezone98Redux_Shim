/*
 * Entry: 00555aa9
 * Name: Chat::AppendMessageSent
 * Namespace: Chat
 * Signature: void AppendMessageSent(Chat * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::AppendMessageSent(Chat *this,char *param_1,char *param_2)

{
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (times_on != 0) {
    AppendTime(this,ChatColor[4].Value);
  }
  _snprintf(local_108,0x100,"<%s> ",param_1);
  AppendNoNewLine(this,ChatColor[5].Value,local_108);
  AppendNoNewLine(this,ChatColor[6].Value,param_2);
  *(undefined1 *)&this[1].hOutput = 1;
  return;
}
