/*
 * Entry: 00512eea
 * Name: IParse_Get_Struct_Array_Element_Count
 * Namespace: Global
 * Signature: int IParse_Get_Struct_Array_Element_Count(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Get_Struct_Array_Element_Count(void *param_1,char *param_2,int *param_3)

{
  _variable_struct *p_Var1;
  
  p_Var1 = IParse_Which_Variable(param_1,param_2);
  if (p_Var1 == (_variable_struct *)0x0) {
    *param_3 = -1;
    return -1;
  }
  *param_3 = 0;
  return p_Var1->struct_element_count;
}
