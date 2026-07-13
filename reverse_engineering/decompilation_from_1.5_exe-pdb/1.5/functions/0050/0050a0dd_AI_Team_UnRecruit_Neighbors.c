/*
 * Entry: 0050a0dd
 * Name: AI_Team_UnRecruit_Neighbors
 * Namespace: Global
 * Signature: void AI_Team_UnRecruit_Neighbors(tag_team * param_1, Mapgrid_Goal * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Team_UnRecruit_Neighbors(tag_team *param_1,Mapgrid_Goal *param_2)

{
  if ((param_2->neighbor_flags & 1) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,-1,-1,1);
  }
  if ((param_2->neighbor_flags & 8) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,-1,0,8);
  }
  if ((param_2->neighbor_flags & 0x20) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,-1,1,0x20);
  }
  if ((param_2->neighbor_flags & 2) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,0,-1,2);
  }
  if ((param_2->neighbor_flags & 0x40) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,0,1,0x40);
  }
  if ((param_2->neighbor_flags & 4) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,1,-1,4);
  }
  if ((param_2->neighbor_flags & 0x10) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,1,0,0x10);
  }
  if ((param_2->neighbor_flags & 0x80) != 0) {
    AI_Team_UnRecruit_Single_Neighbor(param_1,param_2,1,1,0x80);
  }
  param_2->neighbor_flags = '\0';
  return;
}
