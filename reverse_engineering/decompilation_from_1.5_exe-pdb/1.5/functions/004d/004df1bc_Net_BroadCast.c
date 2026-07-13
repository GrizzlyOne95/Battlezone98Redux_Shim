/*
 * Entry: 004df1bc
 * Name: Net_BroadCast
 * Namespace: Global
 * Signature: void Net_BroadCast(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_BroadCast(char *param_1,int param_2)

{
  int iVar1;
  
  if (Net::dp != (dp_s *)0x0) {
    iVar1 = Net::Send(Net::dp,Net::myPlayerID,0,1,param_1,param_2);
    total_bytes_sent = total_bytes_sent + param_2;
    total_msg_sent = total_msg_sent + 1;
    if (iVar1 == 3) {
      DisplayMessage("BroadCast Message Full");
    }
  }
  return;
}
