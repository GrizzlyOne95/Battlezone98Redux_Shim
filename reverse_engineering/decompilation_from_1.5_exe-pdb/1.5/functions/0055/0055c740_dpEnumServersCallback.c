/*
 * Entry: 0055c740
 * Name: dpEnumServersCallback
 * Namespace: Global
 * Signature: int dpEnumServersCallback(char * param_1, long param_2, dp_serverInfo_s * param_3, long * param_4, long param_5, void * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
dpEnumServersCallback
          (char *param_1,long param_2,dp_serverInfo_s *param_3,long *param_4,long param_5,
          void *param_6)

{
  if (serverList != (ServerList *)0x0) {
    if (param_1 == (char *)0x0) {
      ServerList::EndEnum(serverList);
    }
    else {
      ServerList::Enum(serverList,param_1,param_2,(int)param_3->cur_sessTypeUsers);
    }
  }
  return 0;
}
