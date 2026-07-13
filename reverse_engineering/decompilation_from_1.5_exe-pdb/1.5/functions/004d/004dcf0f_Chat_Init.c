/*
 * Entry: 004dcf0f
 * Name: Chat_Init
 * Namespace: Global
 * Signature: void Chat_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Chat_Init(void)

{
  TEXTINPUT_DEF local_94;
  REGION_DEF local_4c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_94.font + 8);
  ToBuf[0] = 'T';
  ToBuf[1] = 'o';
  ToBuf[2] = '\0';
  builtin_strncpy(ToAlliesBuf,"To Allies",10);
  builtin_strncpy(ToAllBuf,"To All",7);
  builtin_strncpy(FromBuf,"From",5);
  builtin_strncpy(BroadcastBuf,"Broadcast",10);
  read_text_label("multi_common","to",ToBuf);
  read_text_label("multi_common","toallies",ToAlliesBuf);
  read_text_label("multi_common","toall",ToAllBuf);
  read_text_label("multi_common","from",FromBuf);
  read_text_label("multi_common","broadcast",BroadcastBuf);
  local_4c.duration = 15.0;
  local_4c.color = chat_color_default;
  builtin_strncpy(local_4c.font,"courier",8);
  local_4c.x = 10;
  local_4c.y = 200;
  local_4c.dx = 0xf0;
  local_4c.dy = 0x5a;
  local_4c.flags = 1;
  chat_display = Scroll_CreateRegion(&local_4c);
  local_94.color = chat_color_self;
  builtin_strncpy(local_94.font,"courier",8);
  local_94.x = 10;
  local_94.y = 300;
  local_94.dx = 0xf0;
  local_94.flags = 0x10;
  local_94.callback = chat_cb;
  local_94.updown_callback = updown_callback;
  chat_entry = TextInput_CreateRegion(&local_94);
  chat_show = 1;
  Scroll_ShowRegion(chat_display,1);
  return;
}
