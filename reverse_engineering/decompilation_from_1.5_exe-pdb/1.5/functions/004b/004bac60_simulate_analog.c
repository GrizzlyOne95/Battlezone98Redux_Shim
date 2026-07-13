/*
 * Entry: 004bac60
 * Name: simulate_analog
 * Namespace: Global
 * Signature: int simulate_analog(ANALOG_SOURCE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl simulate_analog(ANALOG_SOURCE *param_1)

{
  ANALOG_SINK *pAVar1;
  int *piVar2;
  long extraout_EAX;
  char *pcVar3;
  int extraout_EAX_00;
  int extraout_EAX_01;
  
  pAVar1 = param_1->sink;
  if ((pAVar1->reset_discrete == (char *)0x0) || (*pAVar1->reset_discrete == '\0')) {
    param_1 = (ANALOG_SOURCE *)(int)pAVar1->simulated;
    if ((pAVar1->set_discrete == (char *)0x0) || (*pAVar1->set_discrete == '\0')) goto LAB_004bacef;
    *pAVar1->delta = 0;
    _ftol2_sse();
    pAVar1->current = extraout_EAX;
    pcVar3 = pAVar1->set_discrete;
  }
  else {
    if (param_1->from != (long *)0x0) {
      (*input_funcs[param_1->device]->reset)(input_desc[param_1->device].data,param_1->channel);
    }
    *pAVar1->delta = 0;
    pAVar1->current = pAVar1->zero;
    pcVar3 = pAVar1->reset_discrete;
  }
  param_1 = (ANALOG_SOURCE *)0x1;
  *pcVar3 = '\0';
LAB_004bacef:
  if (pAVar1->simulated == '\0') {
    TimeStepLocal();
    if ((pAVar1->plus_discrete != (char *)0x0) && (*pAVar1->plus_discrete != '\0')) {
      if (*pAVar1->delta < 0) {
        *pAVar1->delta = 0;
      }
      piVar2 = pAVar1->delta;
      _ftol2_sse();
      *piVar2 = *piVar2 + extraout_EAX_00;
      if (0x5555 < *pAVar1->delta) {
        *pAVar1->delta = 0x5555;
      }
      pAVar1->current = pAVar1->current + *pAVar1->delta;
      if (0x10000 < pAVar1->current) {
        pAVar1->current = 0x10000;
      }
      param_1 = (ANALOG_SOURCE *)0x1;
      *pAVar1->plus_discrete = '\0';
    }
    if ((pAVar1->minus_discrete != (char *)0x0) && (*pAVar1->minus_discrete != '\0')) {
      if (0 < *pAVar1->delta) {
        *pAVar1->delta = 0;
      }
      piVar2 = pAVar1->delta;
      _ftol2_sse();
      *piVar2 = *piVar2 + extraout_EAX_01;
      if (*pAVar1->delta < -0x5555) {
        *pAVar1->delta = -0x5555;
      }
      pAVar1->current = pAVar1->current + *pAVar1->delta;
      if (pAVar1->current < -0x10000) {
        pAVar1->current = -0x10000;
      }
      param_1 = (ANALOG_SOURCE *)0x1;
      *pAVar1->minus_discrete = '\0';
    }
    if (param_1 == (ANALOG_SOURCE *)0x0) {
      *pAVar1->delta = 0;
    }
  }
  pAVar1->simulated = (char)param_1;
  return (int)param_1;
}
