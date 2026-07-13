/*
 * Entry: 0045ff80
 * Name: Patrol
 * Namespace: Global
 * Signature: void Patrol(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Patrol(int param_1,char *param_2,int param_3)

{
  SetIndependence(param_1,1);
  SetPathType(param_2,LOOP_PATH);
  Goto(param_1,param_2,param_3);
  return;
}
