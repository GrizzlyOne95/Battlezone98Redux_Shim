/*
 * Entry: 004968b4
 * Name: GameObject_SetUserTeamAlly
 * Namespace: Global
 * Signature: void GameObject_SetUserTeamAlly(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_SetUserTeamAlly(int param_1)

{
  if (param_1 != GameObject::userTeamNumber) {
    Team::Ally(GameObject::userTeamList,param_1);
    FlagDisplay::MakeTexture(&flagDisplay);
    return;
  }
  return;
}
