/*
 * Entry: 00507c58
 * Name: AI_AIPLoad
 * Namespace: Global
 * Signature: tagAIP_struct * AI_AIPLoad(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

tagAIP_struct * __cdecl AI_AIPLoad(int param_1,char *param_2)

{
  int iVar1;
  tagAIP_struct *ptVar2;
  char local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  Debug_Assert(aip_initialised,0x65b,".\\Schedule\\Ai.cpp","aip_initialised");
  iVar1 = AI_MakeFilename(local_10c,param_2);
  if (iVar1 != 0) {
    tlog_gdm("Loading AIP \'%s\'\n");
    ptVar2 = AIP_load_AIP(local_10c);
    if (ptVar2 != (tagAIP_struct *)0x0) {
      C_Linked_List_Add_Data(&aip_list,ptVar2);
      tlog_gdm("  Loaded OK");
      return ptVar2;
    }
  }
  _tlog_filename = ".\\Schedule\\Ai.cpp";
  _tlog_line = 0x66e;
  tlog(1,"Could not find / could not load AIP \'%s\'");
  return (tagAIP_struct *)0x0;
}
