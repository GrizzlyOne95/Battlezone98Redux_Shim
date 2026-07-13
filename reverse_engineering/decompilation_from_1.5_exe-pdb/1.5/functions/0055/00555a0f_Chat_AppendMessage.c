/*
 * Entry: 00555a0f
 * Name: Chat::AppendMessage
 * Namespace: Chat
 * Signature: void AppendMessage(Chat * this, char * param_1, uint param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::AppendMessage(Chat *this,char *param_1,uint param_2,char *param_3)

{
  undefined1 auStack_508 [1024];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (times_on != 0) {
    AppendTime(this,ChatColor[1].Value);
  }
  _snprintf(local_108,0x100,"<%s> ",param_1);
  AppendNoNewLine(this,ChatColor[2].Value,local_108);
  auStack_508[param_2] = 0;
  AppendNoNewLine(this,ChatColor[3].Value,param_3);
  *(undefined1 *)&this[1].hOutput = 1;
  return;
}
