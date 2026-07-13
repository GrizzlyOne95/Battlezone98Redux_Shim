/*
 * Entry: 004ddb70
 * Name: Net_Send
 * Namespace: Global
 * Signature: int Net_Send(dp_s * param_1, ushort param_2, ushort param_3, int param_4, void * param_5, uint param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Net_Send(dp_s *param_1,ushort param_2,ushort param_3,int param_4,void *param_5,uint param_6)

{
  int iVar1;
  
  iVar1 = Net::Send(param_1,param_2,param_3,param_4,param_5,param_6);
  return iVar1;
}
