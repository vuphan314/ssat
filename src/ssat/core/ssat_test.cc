/**CFile****************************************************************
  FileName    [ssat_test.cc]
  SystemName  []
  PackageName []
  Synopsis    [An example file to use Catch2 writing test case]
  Author      [Kuan-Hua Tu]
  
  Affiliation [NTU]
  Date        [2018.04.20]
***********************************************************************/

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include "extUnitTest/catch.hpp"
#include "SsatSolver.h"
using namespace Minisat;

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

TEST_CASE( "toliet" , "[planning]" )
{
   char cwd[1024], * targetFile;
   abctime clk = Abc_Clock();
   Ssat_Params_t Params , * pParams = &Params;
   // get current dir and target file name
   getcwd(cwd, sizeof(cwd));
   printf("  > Current working dir: %s\n", cwd);
   targetFile = strcat(cwd, "/expSsat/ssatER/planning/ToiletA/toilet_a_10_01.2.qdimacs");
   printf("  > Testing target: %s\n", targetFile);
   // set defaults
   memset( pParams , 0 , sizeof(Ssat_Params_t) );
   pParams->range    = 0.0;
   pParams->upper    = -1;
   pParams->lower    = -1;
   pParams->fGreedy  = true;
   pParams->fSub     = true;
   pParams->fPart    = true;
   pParams->fBdd     = true;
   pParams->fDynamic = true;
   pParams->fIncre   = true;
   pParams->fCkt     = true;
   pParams->fPure    = true;
   pParams->fAll     = true;
   pParams->fMini    = true;
   pParams->fTimer   = true;
   pParams->fVerbose = true;
   gzFile in = gzopen( targetFile, "rb" );
   SsatSolver * pSsat = new SsatSolver( pParams->fTimer , pParams->fVerbose );
   pSsat->readSSAT(in);
   gzclose(in);
   pSsat->solveSsat( pParams );
   double answer = pSsat->lowerBound();
   REQUIRE( answer == Approx(0.001953125) );
   delete pSsat;
   Abc_PrintTime( 1 , "  > Elasped time" , Abc_Clock()-clk );
}

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////
