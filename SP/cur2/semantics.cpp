/* $mlisp18 */
#include "semantics.h"
#include "semempty.cpp"
using namespace std;
void tSM::init(){
    globals.clear();
    locals.clear();
    params.clear();
    scope = 0; // ���������� �������
//���������:
    globals["e"] = 
    tgName(VAR|DEFINED|BUILT);
    globals["pi"] = 
    tgName(VAR|DEFINED|BUILT);

// ������������ ���������:
    globals["remainder"] =
    tgName(PROC|DEFINED|BUILT, 2);
    globals["abs"] =
    tgName(PROC|DEFINED|BUILT, 1);
    globals["display"] = 
    tgName(PROC|DEFINED|BUILT, 1);
    globals["newline"] = 
    tgName(PROC|DEFINED|BUILT, 0);
    globals["quotient"] = 
    tgName(PROC|DEFINED|BUILT, 2);
    globals["expt"] = 
    tgName(PROC|DEFINED|BUILT, 2);
// ...
// ������ �� ���������, ������� ������������
// � ����� ����������� �������
	return;
}
int tSM::p01() { //       S -> PROG
    bool error = false;
    for (tGlobal::iterator it=globals.begin(); it!=globals.end(); ++it) {
// ����������� ������� ���������� ����
// � � ��������� �� ������� ������� �����
// ���� ���������, �� �� ������������ ��������,
// � ����� ��������������, �� �� ������������
// ���������� ����������. ��������� �������� [!].
// ����� ����, ������������ ��� ���� ������������,
// �� �� �������������� ���������� � ����������,
// �� ����������� ����������. ��������� �������� [?].
//   it->first   ���
//   it->second  ������� ������
// ...
        if (it->second.test(USED) && !it->second.test(DEFINED)) {
        	error = true;
			if (it->second.test(PROC)) {
				ferror_message += "[!]Procedure application:"
				                  "  '"+ it->first +
				                  "' was used and not defined\n";
			} else {
				ferror_message += "[!]Variable application:"
				                  "  '"+ it->first +
				                  "' was used and not defined\n";
			}
	    }
	    
	    if (!it->second.test(USED) && it->second.test(DEFINED) && !it->second.test(BUILT)) {
			if (it->second.test(PROC)) {
				ferror_message += "[?]Procedure application: "
				                  "'"+ it->first +
				                  "' was defined and not used\n";
			} else {
				ferror_message += "[?]Variable application:"
				                  "  '"+ it->first +
				                  "' was defined and not used\n";
			}
		}
    }//for...
    if (error) {
	    return 1;
	}
	return 0;
}
int tSM::p13() { //       E -> $id
    string name = S1->name;
    if (scope > 1) {// ��������� �������
        if (locals.count(name)) {// ��������� ���
		    return 0;
        }
    } // if scope
    if (scope > 0) {// ������� ����������
        if (params.count(name)) {// ��� ���������
        return 0;
        }// if params...
    }// if scope... 
    
    //���� ��� � ������� ���������� ���
    tgName& ref = globals[name];
    
    //��� �������
    if(ref.test(PROC)) {
		//��������� ������ ������������
		//������ VAR ��� ��������� ��� ��������
		ferror_message = "[!]Procedure application:"
		                 "  '" + name +
		                 "' procedure can't be used as a parameter";
	  	return 1;
	}
	if (ref.empty()) {
		//��� �� �����������
		ref.set(USED);
		ref.set(VAR);
		return 0;
    }
	if (!ref.test(USED)) {
		//����������� � �� ��������������
		ref.set(USED);
	}
	
	return 0;
}

int tSM::p21() { //    .   E -> CPROC
    string name = S1->name;
    int   count = S1->count;
    if(scope > 1) {// ��������� �������
        if (locals.count(name)) {// ��������� ���
//p21-1.ss
        ferror_message = "[!]Procedure application:"
                         " local variable '"+name+
                         "' shadows the procedure!";
        return 1;
        } // if locals ...
    } // if scope ...
    if (scope > 0) {// ������� ����������
        if(params.count(name)) {// ��� ���������
//p21-2.ss
            ferror_message = "[!]Procedure application:"
                             " parameter '" + name +
                             "' shadows the procedure!";
            return 1;
        }// if params...
    }// if scope... 
    do {
//  ����� ��� � ���������� �������
        tgName& ref = globals[name];
        if (ref.empty()) {//����������� ���
//          ������� ����� ������� ������
            ref = tgName(PROC|USED, count);
            break;
        }

// ��� �������
        if(!ref.test(PROC)){//�� ���������
//p21-3.ss
        ferror_message = "[!]Procedure application:"
                         "  '"+ name+
                         "' is not a procedure!";
        return 1;
        }

    if (ref.arity != count) {//����� ����������
//                �� ����� ����� ���������� 
        std::ostringstream buf;
        buf << "[!]Procedure application: '" << name << "' "
//p21-4.ss
        << (ref.test(DEFINED) ? "expects " // ���������
//                                      ��� ����������
//p21-5.ss

// ��������� ��� �� ����������, �� ��� ���������� �����         
            : "has been called already\n\t with ")
        << ref.arity << " argument"
        << (ref.arity != 1 ? "s" : "")
        << ", given: " << count << " !";
        ferror_message = buf.str();
        return 1;
    }
// ������ ���
    ref.set(USED);//��� ������������
   } while (false);

	return 0;
}
	
int tSM::p50() { //  HCPROC -> ( $id
    S1->name = S2->name;
    S1->count = 0;
	return 0;
} //����� ��������� ��������� ����� �����������
	
int tSM::p51() { //  HCPROC -> HCPROC E
    ++S1->count;
	return 0;
} 

int tSM::p58() { //   CPRED -> HCPRED )
    string name = S1->name;
	int    count= S1->count;
	
	do {
//  ����� ��� � ���������� �������
        tgName& ref = globals[name];
        if (ref.empty()) {//����������� ���
//        ������� ����� ������� ������
            ref = tgName(PROC|USED, count);
            break;
        }

        if(ref.arity != count) {//����� ���������� �� ����� ����� ���������� 
            std::ostringstream buf;
            buf<<"[!]Procedure application: '" << name << "' "
            //p21-4.ss
            << (ref.test(DEFINED) ? "expects " : "has been called already\n\t with "
                ) 
            << ref.arity << " argument"
            << (ref.arity != 1 ? "s" : "")
            << ", given: "<<count<<" !";
            ferror_message = buf.str();
            return 1;
        }
// ������ ���
        ref.set(USED);//��� ������������
    } while (false);

	return 0;
}
int tSM::p59() { //  HCPRED -> ( $idq
    S1->name = S2->name;
	S1->count = 0;
	return 0;
}

int tSM::p60(){ //  HCPRED -> HCPRED E
    ++S1->count;
	return 0;}
	
int tSM::p78(){ //    HSET -> ( set! $id
    string name = S3->name;
    if (scope > 1) {// ��������� �������
        if (locals.count(name)) {// ��������� ���
		    return 0;
        }
    } // if scope
    if (scope > 0) {// ������� ����������
        if (params.count(name)) {// ��� ���������
        return 0;
        }// if params...
    }// if scope... 
    
    //���� ��� � ������� ���������� ���
    tgName& ref = globals[name];
    
    //��� �������
    if (ref.test(PROC)) {
		//��������� ������ ������������
		//������ VAR, ��������� ��� ��������
		ferror_message = "[!]Procedure application:"
		                 "  '" + name +
		                 "' procedure can't be redefined";
	  	return 1;
	}
	if (ref.empty()) {
		//��� �� �����������
		ref.set(USED);
		ref.set(VAR);
		return 1;
    }
	if (!ref.test(USED)) {
		//����������� � �� ��������������
		ref.set(USED);
	}
	if (ref.test(VAR) && ref.test(BUILT)) {
		ferror_message = "[!]Procedure application:"
		                 "  '" + name +
		                 "' constant can't be redefined";
	  	return 1;
	}
	return 0;
}

int tSM::p89(){ //    PRED -> HPRED BOOL )
    string name = S1->name;
	int   count = S1->count;
	
	tgName& ref = globals[name];
	
	if(ref.empty()) {
		ref = tgName(PROC|DEFINED, count);
    } else if(ref.test(DEFINED)){
		    ferror_message = "[!]Procedure definition:"
		                     " '" + name +
		                     "' was already defined";
		    return 1;
	} else {
		ref.set(DEFINED);	
    }
	params.clear();
	scope = 0;
	return 0;
}
int tSM::p90() { //   HPRED -> PDPAR )
    scope = 1;
	return 0;
}
int tSM::p91() { //   PDPAR -> ( define ( $idq
    //����������� ���������
	S1->name = S4->name;
	S1->count = 0;
	return 0;
}
int tSM::p92() { //   PDPAR -> PDPAR $id
    if (params.count(S2->name)) {
	    ferror_message = "[!]Predicate definition: in '"
		                 + S1->name+
		                 "' duplicate parameter identifier '"
		                 + S2->name + "'!";
	    return 1;
	}
	params.insert(S2->name);
	++S1->count;
	return 0;
}
int tSM::p95() { //    HVAR -> ( define $id
    //����������� ���������� ����������
	string name = S3->name;
	tgName& ref = globals[name];
	
	if (ref.empty()) {//����������� ���
		//������� ����� ������� ������
		ref.set(VAR);
		ref.set(DEFINED);
		return 0;
	}
	
	if (ref.test(PROC) && ref.test(USED)) {
		ferror_message = "[!]Global variable definition:"
			             " '" + name +
			             "' was already declared as procedure";
		return 1;
	} //����������� ������ ����������� ���������
	
	if (ref.test(DEFINED)) {
		ferror_message = "[!]Global variable definition:"
			             " Trying to redefine '" + name +
			             "'";
		return 1;
	}
	return 0;
}
int tSM::p96() { //    PROC -> HPROC LETLOC )
    string name = S1->name;
	int    count= S1->count;
	tgName& ref = globals[name];
	if(ref.empty()) {
		ref = tgName(PROC|DEFINED, count);
	} else if (ref.test(VAR)) {
		ferror_message = "[!]Procedure definition:"
		                 " '"+ name +
		                 "' was already defined as variable";
		return 1;
	} else if(ref.test(DEFINED)) {
		ferror_message = "[!]Procedure definition:"
		                 " '"+ name +
		                 "' was already defined";
		return 1;
	} else {
		ref.set(DEFINED);
	}
    params.clear();
    scope = 0;
	return 0;
}
int tSM::p97() { //    PROC -> HPROC E1 )
    string name = S1->name;
	int    count= S1->count;
	tgName& ref = globals[name];
	if(ref.empty()) {
		//�� ���� ����������
		ref = tgName(PROC|DEFINED, count);
	} else if (ref.test(VAR)) {
		ferror_message = "[!]Procedure definition:"
		                 " '" + name +
		                  "' was already defined as variable";
		return 1;
	} else if(ref.test(DEFINED)) {
		ferror_message = "[!]Procedure definition:"
	         	         " '" + name +
		                 "' was already defined";
		return 1;
	} else {
		ref.set(DEFINED);		
	}
    params.clear();
    scope = 0;
	return 0;
}
int tSM::p98() { //   HPROC -> PCPAR )
    scope = 1;
	return 0;
}
int tSM::p100() { //   PCPAR -> ( define ( $id
    S1->name = S4->name;
    S1->count = 0;
	return 0;
}
int tSM::p101(){ //   PCPAR -> PCPAR $id
    if(params.count(S2->name)){
    //p101-1.ss
        ferror_message = "[!]Procedure definition: in '"
        				 + S1->name +
        				 "' duplicate parameter identifier '"
        				 +S2->name+"'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
	return 0;
}
int tSM::p102() { //  LETLOC -> HLETLOC E1 )
    locals.clear();
    scope = 1;
	return 0;
}
int tSM::p103() { // HLETLOC -> LTVAR )
    scope=2;
	return 0;
}
int tSM::p105() { //   LTVAR -> ( let ( CPROC
    S1->name = S4->name;
	S1->count = 1;
	locals.insert(S4->name);
	return 0;
}
int tSM::p106() { //   LTVAR -> LTVAR CPROC
    if(locals.count(S2->name)) {
		ferror_message = "[!]Local variables definition: in '"
						 +S1->name+
						 "' duplicate variable definition'"
						 +S2->name+"'!";
	    return 1;
	}
	locals.insert(S2->name);
	++S1->count;
	return 0;
}	
//_____________________


