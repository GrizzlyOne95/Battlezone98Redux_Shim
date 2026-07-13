/*
 * Entry: 00555d3c
 * Name: Chat::Append
 * Namespace: Chat
 * Signature: void Append(Chat * this, ulong param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::Append(Chat *this,ulong param_1,char *param_2)

{
  char *in_stack_0000000c;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,in_stack_0000000c,&stack0x00000010);
  AppendNoNewLine((Chat *)param_1,(ulong)param_2,local_408);
  *(undefined1 *)(param_1 + 4) = 1;
  return;
}
