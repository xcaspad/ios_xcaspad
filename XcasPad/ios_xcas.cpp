// -*- mode:C++ ; compile-command: "g++ -I.. -g -c cas2.cc" -*-

#include <string>
#include <stdexcept>
#include <pthread.h> 

#include <signal.h>
#include <unistd.h>

#include "first.h"
#include "gen.h"

#include "prog.h"
#include "identificateur.h"
#include "symbolic.h"
#include "identificateur.h"
#include "usual.h"
#include "sym2poly.h"
#include "subst.h"
#include "plot.h"
#include "tex.h"
#include "mathml.h"
#include "input_parser.h"
#include "input_lexer.h"
#include "rpn.h"
#include "help.h"
#include "ti89.h" // for _unarchive_ti
//#include "permu.h"
#include "modpoly.h"
#include "unary.h"
#include "input_lexer.h"
#include "maple.h"
#include "derive.h"
#include "giacintl.h"
#include "misc.h"
#include "lin.h"
#include "pari.h"
#include "intg.h"



using namespace std;
using namespace giac;

giac::context giac_context;
giac::context * contextptr;

string current_graphic;


extern "C" {

const char* resultFromGiacTex(const char* computation);

const char* parseFromGiacTex(const char* computation);

}

const char* resultFromGiacTex(const char* computation){
	
	gen *g, e;
	//const char *compute = env->GetStringUTFChars(computation, 0);

    try{
        g = new gen(computation, contextptr);
        e = eval(*g, contextptr);

        string t = gen2tex(e, contextptr);

        free(g);
        e = NULL;

        t = "$$" + t + "$$";
        return t.c_str();
    }
    catch (std::runtime_error & err){
        return err.what();
    }
}

const char* parseFromGiacTex(const char* computation){
	

	gen *g;
	//const char *compute = env->GetStringUTFChars(computation, 0);
    try{
        g = new gen(computation, contextptr);

        string s = "$$" + gen2tex(*g, contextptr) + "$$";

        return s.c_str();
    }
    catch (std::runtime_error & err){
        return err.what();
    }
}



