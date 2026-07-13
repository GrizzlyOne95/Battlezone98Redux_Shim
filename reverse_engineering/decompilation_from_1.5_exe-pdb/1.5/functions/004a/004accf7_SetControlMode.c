/*
 * Entry: 004accf7
 * Name: SetControlMode
 * Namespace: Global
 * Signature: void SetControlMode(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetControlMode(int param_1)

{
  if (controlMode != param_1) {
    controlMode = param_1;
    InformMouseOfVideoModeChange();
    return;
  }
  return;
}
