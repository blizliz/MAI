/* $mlisp18 */
int tSM::p02(){ //    PROG -> CALCS1
	return 0;}
int tSM::p03(){ //    PROG -> DEFS
	return 0;}
int tSM::p04(){ //    PROG -> DEFS CALCS1
	return 0;}
int tSM::p05(){ //  CALCS1 -> CALCS
	return 0;}
int tSM::p06(){ //   CALCS -> CALC
	return 0;}
int tSM::p07(){ //   CALCS -> CALCS CALC
	return 0;}
int tSM::p08(){ //    CALC -> E1
	return 0;}
int tSM::p09(){ //    CALC -> BOOL
	return 0;}
int tSM::p10(){ //    CALC -> STR
	return 0;}
int tSM::p11(){ //    CALC -> DISPSET
	return 0;}
int tSM::p12(){ //      E1 -> E
	return 0;}
int tSM::p14(){ //       E -> CONST
	return 0;}
int tSM::p15(){ //       E -> ADD
	return 0;}
int tSM::p16(){ //       E -> SUB
	return 0;}
int tSM::p17(){ //       E -> DIV
	return 0;}
int tSM::p18(){ //       E -> MUL
	return 0;}
int tSM::p19(){ //       E -> COND
	return 0;}
int tSM::p20(){ //       E -> IF
	return 0;}
int tSM::p22(){ //   CONST -> $zero
	return 0;}
int tSM::p23(){ //   CONST -> $dec
	return 0;}
int tSM::p24(){ //     ADD -> HADD E1 )
	return 0;}
int tSM::p25(){ //    HADD -> ( +
	return 0;}
int tSM::p26(){ //    HADD -> HADD E1
	return 0;}
int tSM::p27(){ //     SUB -> HSUB E1 )
	return 0;}
int tSM::p28(){ //    HSUB -> ( -
	return 0;}
int tSM::p29(){ //    HSUB -> HSUB E1
	return 0;}
int tSM::p30(){ //     DIV -> HDIV E1 )
	return 0;}
int tSM::p31(){ //    HDIV -> ( /
	return 0;}
int tSM::p32(){ //    HDIV -> HDIV E1
	return 0;}
int tSM::p33(){ //     MUL -> HMUL E1 )
	return 0;}
int tSM::p34(){ //    HMUL -> ( *
	return 0;}
int tSM::p35(){ //    HMUL -> HMUL E1
	return 0;}
int tSM::p36(){ //    COND -> HCOND ELSE )
	return 0;}
int tSM::p37(){ //    COND -> HCOND CLAUS )
	return 0;}
int tSM::p38(){ //   HCOND -> ( cond
	return 0;}
int tSM::p39(){ //   HCOND -> HCOND CLAUS
	return 0;}
int tSM::p40(){ //   CLAUS -> HCLAUS E1 )
	return 0;}
int tSM::p41(){ //  HCLAUS -> ( BOOL
	return 0;}
int tSM::p42(){ //  HCLAUS -> HCLAUS DISPSET
	return 0;}
int tSM::p43(){ //    ELSE -> HELSE E1 )
	return 0;}
int tSM::p44(){ //   HELSE -> ( else
	return 0;}
int tSM::p45(){ //   HELSE -> HELSE DISPSET
	return 0;}
int tSM::p46(){ //      IF -> IFTRUE E1 )
	return 0;}
int tSM::p47(){ //  IFTRUE -> HIF E
	return 0;}
int tSM::p48(){ //     HIF -> ( if BOOL
	return 0;}
int tSM::p49(){ //   CPROC -> HCPROC )
	return 0;}
int tSM::p52(){ //    BOOL -> $bool
	return 0;}
int tSM::p53(){ //    BOOL -> CPRED
	return 0;}
int tSM::p54(){ //    BOOL -> REL
	return 0;}
int tSM::p55(){ //    BOOL -> OR
	return 0;}
int tSM::p56(){ //    BOOL -> AND
	return 0;}
int tSM::p57(){ //    BOOL -> ( not BOOL )
	return 0;}
int tSM::p61(){ //     REL -> HREL E1 )
	return 0;}
int tSM::p62(){ //    HREL -> ( < E
	return 0;}
int tSM::p63(){ //    HREL -> ( = E
	return 0;}
int tSM::p64(){ //    HREL -> ( > E
	return 0;}
int tSM::p65(){ //    HREL -> ( >= E
	return 0;}
int tSM::p66(){ //    HREL -> ( <= E
	return 0;}
int tSM::p67(){ //      OR -> HOR BOOL )
	return 0;}
int tSM::p68(){ //     HOR -> ( or
	return 0;}
int tSM::p69(){ //     HOR -> HOR BOOL
	return 0;}
int tSM::p70(){ //     AND -> HAND BOOL )
	return 0;}
int tSM::p71(){ //    HAND -> ( and
	return 0;}
int tSM::p72(){ //    HAND -> HAND BOOL
	return 0;}
int tSM::p73(){ //     STR -> $str
	return 0;}
int tSM::p74(){ //     STR -> SIF
	return 0;}
int tSM::p75(){ //     SIF -> SIFTRUE STR )
	return 0;}
int tSM::p76(){ // SIFTRUE -> HIF STR
	return 0;}
int tSM::p77(){ //     SET -> HSET E1 )
	return 0;}
int tSM::p79(){ // DISPSET -> ( display E1 )
	return 0;}
int tSM::p80(){ // DISPSET -> ( display BOOL )
	return 0;}
int tSM::p81(){ // DISPSET -> ( display STR )
	return 0;}
int tSM::p82(){ // DISPSET -> ( newline )
	return 0;}
int tSM::p83(){ // DISPSET -> SET
	return 0;}
int tSM::p84(){ //    DEFS -> DEF
	return 0;}
int tSM::p85(){ //    DEFS -> DEFS DEF
	return 0;}
int tSM::p86(){ //     DEF -> PRED
	return 0;}
int tSM::p87(){ //     DEF -> VAR
	return 0;}
int tSM::p88(){ //     DEF -> PROC
	return 0;}
int tSM::p93(){ //     VAR -> VARINI )
	return 0;}
int tSM::p94(){ //  VARINI -> HVAR CONST
	return 0;}
int tSM::p99(){ //   HPROC -> HPROC DISPSET
	return 0;}
int tSM::p104(){ // HLETLOC -> HLETLOC DISPSET
	return 0;}
//_____________________
int tSM::p107(){return 0;} int tSM::p108(){return 0;} 
int tSM::p109(){return 0;} int tSM::p110(){return 0;} 


