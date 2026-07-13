/*
 * Entry: 00509fbd
 * Name: AI_Team_Recruit_Neighbors
 * Namespace: Global
 * Signature: void AI_Team_Recruit_Neighbors(tag_team * param_1, Mapgrid_Goal * param_2, int param_3, int param_4, GameObject * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AI_Team_Recruit_Neighbors
          (tag_team *param_1,Mapgrid_Goal *param_2,int param_3,int param_4,GameObject *param_5)

{
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,-1,-1,1,0x80,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,-1,0,8,0x10,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,-1,1,0x20,4,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,0,-1,2,0x40,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,0,1,0x40,2,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,1,-1,4,0x20,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,1,0,0x10,8,param_3,param_4,param_5);
  AI_Team_Recruit_Single_Neighbor(param_1,param_2,1,1,0x80,1,param_3,param_4,param_5);
  return;
}
