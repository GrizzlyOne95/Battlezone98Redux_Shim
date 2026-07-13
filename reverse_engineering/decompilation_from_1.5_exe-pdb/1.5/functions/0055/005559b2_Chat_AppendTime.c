/*
 * Entry: 005559b2
 * Name: Chat::AppendTime
 * Namespace: Chat
 * Signature: void AppendTime(Chat * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::AppendTime(Chat *this,ulong param_1)

{
  tm *_Tm;
  __time64_t local_20;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_20 = _time64((__time64_t *)0x0);
  _Tm = _localtime64(&local_20);
  strftime(local_18,0x10,"%X ",_Tm);
  AppendNoNewLine(this,param_1,local_18);
  return;
}
