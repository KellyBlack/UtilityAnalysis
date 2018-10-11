#include <iostream>
#include <iomanip>
#include <string>
#include <list>

#include "vector.h"
#include "foundfeasible.h"

//using namespace std;
#define DEBUG


// Routine to see if a given column is already listed in the
// vector of indicies to check.
bool columnExists(Vector<int> *indicies,int currentRow,int value)
{
    // Go through all of the previous entries in the vector.
    for(int lupe=0;lupe<currentRow;++lupe)
        if((*indicies)[lupe]==value)  // If the value exists return true. All done!
            return(true);

    // If we get here the value was not found.
    return(false);
}

// Routine to see if a given collection of columns has already been considered.
// The idea is that if the coresponding entries in the RREF are non-zero, and
// the column numbers are in descending order, then the set has already been
// considered.
bool columnsConsidered(Matrix<double> *rref,
                       Vector<int> *indicies,
                       int currentRow,
                       int currentColumn)
{

    bool considered = false;
    return(false);

    //std::cout << "checking: " << (*indicies)[currentRow] << "/" << currentRow << "/" << currentColumn << " " << std::endl;
    //printVector(*indicies);
    for(int prevColumn=0;!considered && (prevColumn<currentRow);++prevColumn)
    {
        if((*indicies)[prevColumn]>(*indicies)[currentRow])
        {
            // This column may have been considered in a previous iteration.
            for(int rowCheck=0;!considered && (rowCheck<indicies->getLength());++rowCheck)
            {
                /*
                std::cout << std::setw(5) << (*rref)[rowCheck][(*indicies)[rowCheck]]
                          << std::setw(5) << (*rref)[currentRow][(*indicies)[rowCheck]]
                          << std::setw(5) << (*rref)[rowCheck][currentColumn]
                          << std::setw(5) << (*rref)[currentRow][currentColumn]
                               << std::endl;
                */
                if(rowCheck!=prevColumn)
                     considered = considered ||
                             (fabs((*rref)[prevColumn][(*indicies)[prevColumn]] *
                                (*rref)[prevColumn][currentColumn] *
                                (*rref)[rowCheck][(*indicies)[prevColumn]] *
                                (*rref)[rowCheck][currentColumn]) > 1e-4 );
            }
        }
    }

    // if we get here then the set of columns have not been considered previously.
    return(considered);
}

// http://www.netlib.org/lapack/lug/node80.html
// http://www.netlib.org/lapack/explore-html/d7/d3b/group__double_g_esolve_ga5ee879032a8365897c3ba91e3dc8d512.html#ga5ee879032a8365897c3ba91e3dc8d512
// http://www.netlib.org/lapack/explore-html/dd/d9a/group__double_g_ecomputational_ga188b8d30443d14b1a3f7f8331d87ae60.html#ga188b8d30443d14b1a3f7f8331d87ae60


/* *******************************************************************************
 * Routine to check to see if a given set of columns has been previously checked.
 * ******************************************************************************* */
bool columnsPreviouslyChecked(Vector<int> *indicies,
                              std::list<FoundFeasible*> *checkedSets)
{
    bool alreadyChecked = false;
    std::list<FoundFeasible*>::iterator prevChecked;
    for(prevChecked=checkedSets->begin();!alreadyChecked && (prevChecked!=checkedSets->end());++prevChecked)
    {
        // go through each list in the set of previously checked columns. If there is a match then stop the show.
        alreadyChecked = alreadyChecked || (*prevChecked)->match(indicies);
    }
    return(alreadyChecked);
}

/* *******************************************************************************
 * Routine to check a given set of columns and get the condition number for
 * the columns from the original matrix.
 * ******************************************************************************* */
void testFullColumnSet(Matrix<double> *rref,
                       Matrix<double> *originalStoichiometry,
                       squareMatrix<double> *testBasis,
                       int *numberFeasible,
                       Vector<int> *indicies,
                       std::list<FoundFeasible*> *checkedSets,
                       int *numberRepeats)
{
    // form a matrix with the appropriate columns of the original stoichiometry matrix
    testBasis->copyColumnsToRows(originalStoichiometry,indicies);
    if(testBasis->dgetrf()==0)
    {
        // The resulting system is of full rank.
        // Figure out the necessary details.
        //indicies->printVector();


        if(columnsPreviouslyChecked(indicies,checkedSets))
        {
            (*numberRepeats)++;
            //std::cout << "   Previously checked: " << *indicies << std::endl;
            //exit(2);
        }
        else
            *numberFeasible += 1;

        FoundFeasible *newColumns = new FoundFeasible;
        newColumns->clearList();
        for(int foundLupe=0;foundLupe<indicies->getLength();++foundLupe)
        {
            newColumns->addColumn((*indicies)[foundLupe]);
        }
        checkedSets->push_back(newColumns);

    }

}

/* *******************************************************************************
 * Routine to go through the RREF of the matrix and get all combinations of the
 * columns that have non-zero entries in the RREF of the matrix.
 *
 * This is a recursive routine. If starts with the top row and goes through each
 * column with a non-zero entry. For each of those entries it then calls the routine
 * to go through the next row and check each column for the next row. (Repeat!)
 * ******************************************************************************* */
void checkColumns(Matrix<double> *rref,
                  Matrix<double> *originalStoichiometry,
                  squareMatrix<double> *testBasis,
                  Vector<int> *indicies,
                  int *numberFeasible,
                  int currentRow,
                  std::list<FoundFeasible*> *checkedSets,
                  int *numberRepeats
                  )
{
    // Go through each column for the current row. Check to see which entries are
    // non-zero....
    for(int lupe=0;lupe<rref->getNumberColumns();++lupe)
    {
        (*indicies)[currentRow] = lupe;
        if((fabs((*rref)[currentRow][lupe])>1.0e-9)
                && (!columnExists(indicies,currentRow,lupe))
                && (!columnsConsidered(rref,indicies,currentRow,lupe))
                )
        {
            // This entry in the RREF matrix is non-zer0.
            // The column has also not been checked previously.
            // It is a potential column to check.

            // Add this column to the list of columns currently under consideration.
            if( (currentRow+1) >= rref->getNumberRows())
            {
                // We now have a full list of columns to check.
                testFullColumnSet(rref,originalStoichiometry,testBasis,numberFeasible,indicies,checkedSets,numberRepeats);
            }
            else
            {
                // We need at least one more column to check.
                // search using the next row in the RREF matrix.
                checkColumns(rref,originalStoichiometry,testBasis,indicies,numberFeasible,currentRow+1,checkedSets,numberRepeats);
            }
        }
    }
}

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        std::cout << "Error - Command line should include name of file that has the stoichiometry matrix: \"" << argv[0] << " stoich.txt.\"" << std::endl << std::endl;
        exit(1);
    }
    std::cout << argv[1] << std::endl << std::endl << "Starting" << std::endl;
    Vector<double>       v(10,1.0);
    Matrix<double>       stoichiometry(argv[1]);
    Matrix<double>       originalStoich(stoichiometry);
    squareMatrix<double> testBasis(stoichiometry.getNumberRows(),0.0);
    Vector<int>          indicies(stoichiometry.getNumberRows(),-1);

    int numberFeasible = 0;

    std::list<FoundFeasible*> checkedSets;
    int numberRepeats = 0;


    /*
    indicies[0] = 0;
    indicies[1] = 1;
    indicies[2] = 3;
    indicies[3] = 4;
    indicies[4] = 5;
    indicies[5] = 11;
    testBasis.copyColumnsToRows(&stoichiometry,&indicies);
    testBasis.printArray();
    //std::cout << "Result of LU Decomposition: " << testBasis.dgetrf() << std::endl;

    std::cout << "The norm of the matrix: " << testBasis.dlange() << std::endl;
    std::cout << "The reciprocol of the condition number: " << testBasis.dgecon(true) << std::endl;
    testBasis.printArray();
    */

    stoichiometry.printArray();
    stoichiometry.RREF();
    stoichiometry.printArray();
    checkColumns(&stoichiometry,&originalStoich,&testBasis,&indicies,&numberFeasible,0,&checkedSets,&numberRepeats);

    std::cout << "Number Feasible: " << numberFeasible << std::endl;
    std::cout << "Done" << std::endl;

#ifdef DEBUG
    std::cout << "Number of repeats: " << numberRepeats << std::endl;
#endif

    return 0;
}

