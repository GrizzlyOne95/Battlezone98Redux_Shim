/*
 * Entry: 00555c09
 * Name: Chat::AppendWhisperSent
 * Namespace: Chat
 * Signature: void AppendWhisperSent(Chat * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::AppendWhisperSent(Chat *this,char *param_1,char *param_2)

{
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (times_on != 0) {
    AppendTime(this,ChatColor[10].Value);
  }
  local_18[0] = 'T';
  local_18[1] = 'o';
  local_18[2] = 0;
  local_18[3] = '\0';
  local_18[4] = '\0';
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
  read_text_label("multi_message","to_message",local_18);
  _snprintf(local_118,0x100,"<%s: %s> ",local_18,param_1);
  AppendNoNewLine(this,ChatColor[0xb].Value,local_118);
  AppendNoNewLine(this,ChatColor[0xc].Value,param_2);
  *(undefined1 *)&this[1].hOutput = 1;
  return;
}
