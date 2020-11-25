#ifndef switches_included
#define switches_included

#define SW1 BIT0                /* switch 1 is p2.0 */
#define SW2 BIT1                /* switch 2 is p2.1 */
#define SW3 BIT2                /* switch 3 is p2.2 */
#define SW4 BIT3                /* siwtch 4 is p2.3 */
#define SWITCHES (SW1 | SW2 | SW3 | SW4)/* only 4 switches on this board */

void switch_init();
void switch_interrupt_handler();

/* effectively boolean */
extern char switch1_state_down, switch2_state_down, switch3_state_down, switch4_state_down;
extern char switch_state_changed;
#endif // included
