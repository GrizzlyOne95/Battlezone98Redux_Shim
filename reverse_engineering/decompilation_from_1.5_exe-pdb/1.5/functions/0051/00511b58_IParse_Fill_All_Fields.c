/*
 * Entry: 00511b58
 * Name: IParse_Fill_All_Fields
 * Namespace: Global
 * Signature: void IParse_Fill_All_Fields(_domain * param_1, _struct_list_element * param_2, char * * param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
IParse_Fill_All_Fields
          (_domain *param_1,_struct_list_element *param_2,char **param_3,int *param_4,
          double *param_5,char (*param_6) [80],int *param_7,int *param_8)

{
  _field_def *p_Var1;
  
  for (p_Var1 = param_2->the_definition; p_Var1 != (_field_def *)0x0; p_Var1 = p_Var1->next_field) {
    IParse_Fill_Individual_Field
              (param_1,*param_3,p_Var1->field_type,param_4,param_5,param_6,param_7,param_8);
    *param_3 = *param_3 + p_Var1->field_length;
  }
  return;
}
