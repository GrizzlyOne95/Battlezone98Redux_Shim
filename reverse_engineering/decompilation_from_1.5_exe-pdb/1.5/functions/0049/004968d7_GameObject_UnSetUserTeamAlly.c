/*
 * Entry: 004968d7
 * Name: GameObject_UnSetUserTeamAlly
 * Namespace: Global
 * Signature: void GameObject_UnSetUserTeamAlly(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_UnSetUserTeamAlly(int param_1)

{
  if (param_1 != GameObject::userTeamNumber) {
    Team::UnAlly(GameObject::userTeamList,param_1);
    FlagDisplay::MakeTexture(&flagDisplay);
    return;
  }
  return;
}
