//                 lexer.h 2018
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
//********************************************
//*        Developed by  ENB		         *
//*             (c)  2018                    *
//********************************************
class tLexer:public tBaseLexer{
public:
// персональный код разработчика
 std::string Authentication()const{
                     return "ENB"
                +std::string("2018");}
//конструктор
 tLexer():tBaseLexer(){
//создать автоматы:

//  ноль Azero
    addstr  (Azero,0,"+-", 2);
    addstr  (Azero,0,"0",  1);
    addstr  (Azero,2,"0",  1);
  Azero.final(1);

//________________________________________

// число
	addstr  (Adec, 0, "+-", 1);
	addrange(Adec, 0, '1', '9', 2);
	addstr  (Adec, 0, "0", 8);
	addstr  (Adec, 0, ".", 3);
	addrange(Adec, 1, '1', '9', 2);
	addstr  (Adec, 1, ".", 3);
	addstr  (Adec, 1, "0", 8);
	addstr  (Adec, 2, ".", 3);
	addrange(Adec, 2,'0','9',2);
	addstr  (Adec, 2, "eE", 5);
	addrange(Adec, 3,'0','9',4);
	addrange(Adec, 4,'0','9',4);
	addstr  (Adec, 4, "eE", 5);
	addstr  (Adec, 5, "+-", 6);
	addrange(Adec, 6,'0','9',7);
	addrange(Adec, 7,'0','9',7);
	addstr  (Adec, 8, ".", 3);
	addstr  (Adec, 8, "eE", 5);
	
	Adec.final(2);
	Adec.final(4);
	Adec.final(7);
//________________________________________

// идентификатор
	addrange(Aid, 0, 'a', 'z', 1);
	addrange(Aid, 0, 'A', 'Z', 1);
	addrange(Aid, 1, 'a', 'z', 1);
	addrange(Aid, 1 ,'A', 'Z', 1);
	addrange(Aid, 1, '1', '9', 1);
	addstr  (Aid, 1, "-", 1);
	addstr  (Aid, 1, "!", 2);
	addstr  (Aid, 0, "!", 3);

	Aid.final(1);
	Aid.final(2);
	Aid.final(3);
//________________________________________

// идентификатор предиката
	addstr  (Aidq, 0, "?", 1);
	addrange(Aidq, 0, 'a', 'z', 2);
	addrange(Aidq, 0, 'A', 'Z', 2);
	addstr  (Aidq, 0, "-", 3);
	addstr  (Aidq, 1, "?", 1);
	addrange(Aidq, 1, 'a', 'z', 2);
	addrange(Aidq, 1 ,'A', 'Z', 2);
	addrange(Aidq, 1, '1', '9', 2);
	addrange(Aidq, 2, 'a', 'z', 2);
	addrange(Aidq, 2 ,'A', 'Z', 2);
	addrange(Aidq, 2, '1', '9', 2);
	addstr  (Aidq, 2, "-", 3);
	addstr  (Aidq, 2, "?", 4);
	addrange(Aidq, 3, 'a', 'z', 2);
	addrange(Aidq, 3 ,'A', 'Z', 2);
	addrange(Aidq, 3, '1', '9', 2);
	addstr  (Aidq, 3, "-", 3);
	addrange(Aidq, 4, 'a', 'z', 2);
	addrange(Aidq, 4 ,'A', 'Z', 2);
	addrange(Aidq, 4, '1', '9', 2);
	addstr  (Aidq, 4, "-", 3);
	addstr  (Aidq, 4, "?", 4);
    
    Aidq.final(1);
    Aidq.final(4);
}
};
#endif

