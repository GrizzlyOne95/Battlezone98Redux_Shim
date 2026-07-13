/*
 * Entry: 004e3a67
 * Name: Scores_Init
 * Namespace: Global
 * Signature: void Scores_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Scores_Init(void)

{
  char local_808 [128];
  undefined1 local_788 [128];
  char local_708 [256];
  char local_608 [256];
  char local_508 [256];
  char local_408 [256];
  char local_308 [256];
  char local_208 [256];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_788;
  builtin_strncpy(local_108,"Team",5);
  score_show = 1;
  team_score = 1;
  memset(local_108 + 5,0,0xfb);
  builtin_strncpy(local_208,"Player",7);
  memset(local_208 + 7,0,0xf9);
  builtin_strncpy(local_308,"Died",5);
  memset(local_308 + 5,0,0xfb);
  builtin_strncpy(local_408,"Kill",5);
  memset(local_408 + 5,0,0xfb);
  builtin_strncpy(local_708,"Time",5);
  memset(local_708 + 5,0,0xfb);
  builtin_strncpy(local_808,"Life",5);
  memset(local_808 + 5,0,0xfb);
  builtin_strncpy(local_608,"Ping",5);
  memset(local_608 + 5,0,0xfb);
  builtin_strncpy(local_508,"%Loss",6);
  memset(local_508 + 6,0,0xfa);
  read_text_label("multi_common","team",local_108);
  read_text_label("multi_common","player",local_208);
  read_text_label("multi_common","died",local_308);
  read_text_label("multi_common","kill",local_408);
  read_text_label("multi_common","time",local_708);
  read_text_label("multi_common","life",local_808);
  read_text_label("multi_common","ping",local_608);
  read_text_label("multi_common","loss",local_508);
  sprintf(kingPBuf,"%s\t%s\t%s\t%s\t%s\t%s\t%s",local_108,local_208,local_308,local_408,local_708,
          local_608,local_508);
  sprintf(strategyPBuf,"%s\t%s\t%s\t%s\t%s\t%s\t%s",local_108,local_208,local_308,local_408,
          local_808,local_608,local_508);
  sprintf(defaultPBuf,"%s\t%s\t%s\t%s\t%s\t%s",local_108,local_208,local_308,local_408,local_608,
          local_508);
  sprintf(kingBuf,"%s\t%s\t%s\t%s\t%s",local_108,local_208,local_308,local_408,local_708);
  sprintf(strategyBuf,"%s\t%s\t%s\t%s\t%s",local_108,local_208,local_308,local_408,local_808);
  sprintf(defaultBuf,"%s\t%s\t%s\t%s",local_108,local_208,local_308,local_408);
  read_text_label("multi_common","player",player);
  read_text_label("multi_message","ejected",ejected);
  read_text_label("multi_message","ship_destroyed_by",ship_by);
  read_text_label("multi_message","pilot_destroyed_by",pilot_by);
  read_text_label("multi_message","building_destroyed_by",building_by);
  read_text_label("multi_message","killed",killed);
  read_text_label("multi_message","killed_by",killed_by);
  read_text_label("multi_message","ship_destroyed",ship);
  read_text_label("multi_message","building_destroyed",building);
  read_text_label("multi_message","player_joined",joined);
  read_text_label("multi_message","player_left",left);
  read_text_label("multi_message","s_pilot",s_pilot);
  read_text_label("multi_message","sniped",sniped);
  read_text_label("multi_message","sniped_by",sniped_by);
  return;
}
