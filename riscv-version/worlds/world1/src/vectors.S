/*----------------------------------------------------------------------------*/ 
.section    .vectors, "ax"
.align      2
/*----------------------------------------------------------------------------*/

world1_vtb:
    j exception_handler   /*       Exception Handler                */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    j msi_handler         /*       Machine Software Interrupt       */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    j systick_handler     /*       Machine Timer Interrupt          */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    j mei_handler         /*       Machine External Interrupt       */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
/* TODO: Check how to define interrupts */

.size world1_vtb, . - world1_vtb