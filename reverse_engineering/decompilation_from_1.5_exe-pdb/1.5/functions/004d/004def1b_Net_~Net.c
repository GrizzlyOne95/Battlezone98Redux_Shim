/*
 * Entry: 004def1b
 * Name: Net::~Net
 * Namespace: Net
 * Signature: void ~Net(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::~Net(Net *this)

{
  Close(false);
  Chat_Cleanup();
  ALLIE_Cleanup();
  Scores_Cleanup();
  NetPlayer::DelAllPlayers();
  DistributedObject::Cleanup();
  hosting = false;
  runNetworking = false;
  return;
}
