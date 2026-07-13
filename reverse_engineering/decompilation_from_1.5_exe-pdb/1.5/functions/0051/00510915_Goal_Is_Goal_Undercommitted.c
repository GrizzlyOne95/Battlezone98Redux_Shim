/*
 * Entry: 00510915
 * Name: Goal::Is_Goal_Undercommitted
 * Namespace: Goal
 * Signature: int Is_Goal_Undercommitted(Goal * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall Goal::Is_Goal_Undercommitted(Goal *this)

{
  return (uint)((this->the_troop_flow).strength < this->min_required_strength);
}
