;; COPYRIGHT (C) HARRY CLARK 2024

;; SEGA MEGA DRIVE EMULATOR

;; THIS FILE SERVES TO PROVIDE A BASIS FOR BEING ABLE TO 
;; CREATE MACROS EFFICIENTLY IN M68K ASSEMBLY

;; IN A SIMILAR VEIN TO HOW C MACROS WORK, WHEREBY YOU CAN PRINT MESSAGES 
;; USING RAW POINTERS

.SECTION: MACROS

;; CHAR MACRO FOR PRINTING INDIVIDUAL CHARACTERS
;; THIS IS DONE BY DETERMING THE CURRENT STACK POINTER
;; IN RELATION TO ALL OF THE DATA AND ADDRESS REGISTERS

DC.B                CHAR_MAX_MASK                               255
fmt                 DC.B            "%s",                       0
ERR_MSG             DC.B            "Error",                    0                

PRINT_CHAR:     MACRO

    MOVEM.L     D0-D7/A0-A7, -(SP)
    AND         #$FF, D0            ;; MASK THE LSB OF THE 8 BITS OF D0
    SUB         #32,  D0            ;; SUBTRACT IN CASE OF INT OVERFLOW

ENDM

;; IN A SIMILAR VEIN OF THE FUNCTION ABOVE, WE CAN PRINT
;; A CONCURRENT STRING OF CHARACTERS BY USING JUMP TO SUBROUTINE
;; WHICH GOVERNS THE INITIALISATION OF THE NEXT INSTRUCTION
;; AND EVOKES A RETURN TYPE

PRINT_STRING:   MACRO

    MOVEA.L     #0, A3                        ;; CLEAR A3 CACHE ASSUMING THERE IS ANYTHING THERE
    MOVEA.L     #1, A3                        ;; SET WRITE MODE

@LOOP\@

    MOVE.B      (A3)+,D0            
    CMP.B       #CHAR_MAX_MASK, D0            ;; COMPARE EACH CONSECTUTIVE BYTE IN D0, 255 IS THE MAX MASK
    JSR         PRINT_CHAR                    ;; JUMP TO THIS INSTRUCTION TO PRINT OUT EVERY CONSECTUTIVE ELEMENT
    BRA         @LOOP\@                       ;; BRANCH ALWAYS TO THIS SPECIFIC INSTRUCTION ON EVERY EXECUTION OF PRINT_CHAR

    RTS

ENDM

;; AS A OONJUNCTIVE EFFORT OF ALL OF THE PREVIOUS MACROS
;; THIS WILL BE THE MAIN ENCOMPASSING MACRO FOR PRINTING MESSAGES
;; AND VARIOUS OTHER INPUTS

;; SEE https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf#page=74
;; FOR INFORMATION PERTAINING TOWARDS DATA FORMATTING

PRINT_SEMANTIC(fmt, ...)

    LINK        A6, #-8                         ;; ALLOCATE FOR LOCAL VAR
    MOVEA.L     #fmt, A0                        ;; LOAD MESSAGE FORMATTING INTO A0
    CMP.L       #0, D0
    BNE.S       @LOOP\@                         ;; LOOP THROUGH THE STRING WHILE THERE ARE CHARS AVAILABLE IN THE STACK       
    BRA         FREE                            ;; ONCE FINISHED, FREE/EXIT THE PROGRAM

@LOOP\@

     MOVE.L     4(A6), A1                       ;; LOAD THE FIRST VARIADIC ARG FROM THE MACRO
     MOVEA.L    A0, -(A7)                       ;; PUSH MESSAGE ONTO THE STACK
     JSR        PRINT_SEMANTIC

FREE:               MACRO 

    UNLK    A6
    RTS

ENDM

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                          END OF FILE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
