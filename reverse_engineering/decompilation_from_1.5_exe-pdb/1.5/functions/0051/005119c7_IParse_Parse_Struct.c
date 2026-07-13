/*
 * Entry: 005119c7
 * Name: IParse_Parse_Struct
 * Namespace: Global
 * Signature: int IParse_Parse_Struct(_domain * param_1, int param_2, int * param_3, double * param_4, char[80] * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Parse_Struct(_domain *param_1,int param_2,int *param_3,double *param_4,char (*param_5) [80],
                   int *param_6)

{
  _struct_list_element *p_Var1;
  int local_8;
  
  p_Var1 = IParse_Get_New_Struct(*param_5);
  local_8 = 2;
  if (2 < param_2 + -1) {
    do {
      IParse_Add_Next_Field(p_Var1,&local_8,param_2,param_3,param_5);
    } while (local_8 < param_2 + -1);
  }
  p_Var1->next_struct = param_1->the_structs;
  param_1->number_of_structures = param_1->number_of_structures + 1;
  param_1->the_structs = p_Var1;
  return 0;
}
