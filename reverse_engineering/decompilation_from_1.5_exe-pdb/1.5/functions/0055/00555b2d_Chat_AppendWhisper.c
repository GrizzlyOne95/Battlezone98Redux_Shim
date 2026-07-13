/*
 * Entry: 00555b2d
 * Name: Chat::AppendWhisper
 * Namespace: Chat
 * Signature: void AppendWhisper(Chat * this, char * param_1, uint param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::AppendWhisper(Chat *this,char *param_1,uint param_2,char *param_3)

{
  undefined1 auStack_518 [1024];
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (times_on != 0) {
    AppendTime(this,ChatColor[7].Value);
  }
  builtin_strncpy(local_18,"From",5);
  local_18[5] = '\0';
  local_18[6] = '\0';
  local_18[7] = '\0';
  local_18[8] = '\0';
  local_18[9] = '\0';
  local_18[10] = '\0';
  local_18[0xb] = '\0';
  local_18[0xc] = '\0';
  local_18[0xd] = '\0';
  local_18[0xe] = '\0';
  local_18[0xf] = 0;
  read_text_label("multi_message","from_message",local_18);
  _snprintf(local_118,0x100,"<%s: %s> ",local_18,param_1);
  AppendNoNewLine(this,ChatColor[8].Value,local_118);
  auStack_518[param_2] = 0;
  AppendNoNewLine(this,ChatColor[9].Value,param_3);
  *(undefined1 *)&this[1].hOutput = 1;
  return;
}
