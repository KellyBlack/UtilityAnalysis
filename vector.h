#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>


extern "C" {
    //extern void dswap_(int*,double*,int*,double*,int*);
    //extern void daxpy_(int*,double*,double*,int*,double*,int*);
    //extern void dscal_(int*,double*,double*,int*);
    extern void dgetrf_(int*,int*,double*,int*,int*,int*);
    extern void dgecon_(char*,int*,double*,int*,double*,double*,double*,int*,int*);
    extern double dlange_(char*,int*,int*,double*,int*,double*);
}


template <class field>
class vector
{
public:
    vector(int number,field initial=0)
    {
        u = new field[number];
        length = number;
        for(int lupe=0;lupe<number;++lupe)
        {
            u[lupe] = initial;
        }
    }

    ~vector()
    {
      delete [] u;
    }

    field& operator [] (int which)
    {
        return(u[which]);
    }

    field operator [] (int which) const
    {
        return(u[which]);
    }

    explicit operator field*() {return u;}

    int getLength() { return(length);}

    // Routine to print out a vector to the console
    void printVector()
    {
        std::cout << u[0];
        for(int lupe=1;lupe<getLength();++lupe)
            std::cout << "," << u[lupe];
        std::cout << std::endl;
    }


private:
    field *u;
    int length;
};


template <class field>
class matrix
{
public:
    // Default constructor
    matrix()
    {
        u = NULL;
        rows = -1;
        columns = -1;
        index = NULL;
    }

    // Constructor that takes the number rows, columns, and initial value.
    matrix(int numRows,int numColumns,field initial=0)
    {
        rows    = numRows;
        columns = numColumns;
        u = new field*[rows];
        u[0] = new field[rows*columns];
        for(int rowLupe=0;rowLupe<rows;++rowLupe)
        {
            u[rowLupe] = u[0] + rowLupe*columns;
            for(int columnLupe=0;columnLupe<columns;++columnLupe)
            {
                u[rowLupe][columnLupe] = initial;
            }
        }
        createIndexPermutation();
    }

    // Constructor that takes the name of a file and reads the
    // matrix from the file.
    matrix(std::string fileName)
    {
        std::ifstream fp(fileName); // Open a file to read.
        std::string inputLine;
        int lineNumber = 0;

        while(fp)
        {
            std::getline(fp,inputLine);
            if(lineNumber++ <= 0)
            {
                // Ths is the first line in the file.
                // Assume it is in the form of row,column
                int comma = inputLine.find(',');                                   // Figure out where the comma is.
                rows    = std::stoi(inputLine.substr(0,comma));                    // Get the number of rows.
                columns = std::stoi(inputLine.substr(comma+1,inputLine.length())); // Get the number of columns.

                // Allocate the space used by the array.
                u = new field*[rows];
                u[0] = new field[rows*columns];
                for(int rowLupe=0;rowLupe<rows;++rowLupe)
                    u[rowLupe] = u[0] + rowLupe*columns;
            }
            else
            {
                // This is a row that has entries for the matrix.
                // Assume it is comma separated numbers.
                uint comma = inputLine.find(',');  // Figure out where the comma is.
                int columnNumber = 0;
                while((comma>=0) && (comma < inputLine.length()) && (inputLine.length()>0) )
                {
                    std::string number = inputLine.substr(0,comma);           // Get the next number
                    inputLine = inputLine.substr(comma+1,inputLine.length()); // Remove the next number from the line
                    u[lineNumber-2][columnNumber++] = std::stod(number);      // Save the number in the array
                    comma = inputLine.find(',');                              // Figure out where the comma is.
                }

            }
        }

        createIndexPermutation();
        fp.close();
    }

    // Constructor based on a passing another instance of a matrix.
    matrix(matrix<field>& other)
    {
        // Set the number of rows and columns.
        rows = other.getNumberRows();
        columns = other.getNumberColumns();

        // Allocate the space used by the array.
        u = new field*[rows];
        u[0] = new field[rows*columns];
        for(int rowLupe=0;rowLupe<rows;++rowLupe)
            u[rowLupe] = u[0] + rowLupe*columns;

        // Finally copy everything over....
        for(int rowLupe=0;rowLupe<rows;++rowLupe)
            for(int colLupe=0;colLupe<columns;++colLupe)
            {
                u[rowLupe][colLupe] = other[rowLupe][colLupe];
            }

        createIndexPermutation();
    }


    // routine to initialize the index vector that holds the current row permutations.
    void createIndexPermutation()
    {
        // Create the index vector that holds the row permutations.
        index = new int[rows];
        int *ptr = index;
        for(int lupe=0;lupe<rows;++lupe)
            *ptr++ = lupe;  // set the inital value to be the same row number so not permutations.
    }

    // Destructor that deletes the memory allocated in the vector u.
    ~matrix()
    {
        delete u[0];
        delete [] u;
        rows = -1;
        columns = -1;
    }


    // Routine to get a pointer to one row of the matrix using the [] operator
    field*& operator [] (int which)
    {
        if(which >= rows)
        {
            std::cout << "Row number out of bounds" << std::endl;
            exit(1);
        }
        return(u[which]);
    }

    // Routine to get a pointer to one row of the matrix using the [] operator
    field* operator [] (int which) const
    {
        if(which >= rows)
        {
            std::cout << "Row number out of bounds" << std::endl;
            exit(1);
        }
        return(u[which]);
    }

    // Routine used for assignment
    matrix& operator= (matrix<field>& other)
    {
        if(this != &other)
        {
            if(rows >= 0)
            {
                // Need to delete the current memory....
                delete u[0];
                delete [] u;
            }

            // Set the number of rows and columns.
            rows = other.getNumberRows();
            columns = other.getNumberColumns();

            // Allocate the space used by the array.
            u = new field*[rows];
            u[0] = new field[rows*columns];
            for(int rowLupe=0;rowLupe<rows;++rowLupe)
                u[rowLupe] = u[0] + rowLupe*columns;

            // Finally copy everything over....
            for(int rowLupe=0;rowLupe<rows;++rowLupe)
            {
                index[rowLupe] = other.getRowIndex(rowLupe);
                for(int colLupe=0;colLupe<columns;++colLupe)
                {
                    u[rowLupe][colLupe] = other[rowLupe][colLupe];
                }
            }

        }

        return(*this);
    }

    // Routine to get the data when casting the type
    explicit operator field*() {return u[0];}

    // routine to get the number of rows in the matrix
    int getNumberRows() { return(rows);}

    // routine to get the number of columnss in the matrix
    int getNumberColumns() { return(columns);}

    // Routine to get the value of the index vector at a certain place.
    int getRowIndex(int which)
    {
        return(index[which]);
    }

    /* **************************************************************
     * Routine to swap two given rows in the matrix.
     * ************************************************************** */
    void swapRows(int firstRow,int secondRow)
    {
        // Set up the pointers to point at the first entry in each row.
        field *ptr1 = u[firstRow];
        field *ptr2 = u[secondRow];

        // intermediate values and loop variables required for the loop.
        field tmp;
        int lupe;

        for(lupe=0;lupe<columns;++lupe)
        {
            // go through each entry in the vectors and exchange them.
            tmp = *ptr1;
            *ptr1++ = *ptr2;
            *ptr2++ = tmp;
        }
    }

    /* **************************************************************
     * Routine to add one row of the matrix multipled by a constant
     * to another row in the matrix.
     * ************************************************************** */
    void daxpy(field scaleValue,int changedRow,int sourceRow,int startColumn)
    {
        // Set up the pointers to point at the first entry in each row.
        field *ptr1 = u[changedRow]+startColumn;
        field *ptr2 = u[sourceRow]+startColumn;

        for(int lupe=startColumn;lupe<columns;++lupe)
        {
            // go through each entry and perform the scale/add opteration
            *ptr1++ += scaleValue*(*ptr2++);
        }
    }

    /* **************************************************************
     * Routine to go through a row in the matrix and multiply by a
     * scalar value.
     * ************************************************************** */
    void dscal(field scaleValue,int whichRow,int startColumn)
    {
        // set up the pointer to point at the first entry in the row
        field *ptr = u[whichRow] + startColumn;

        // scale every entry in the vector.
        for(int lupe=startColumn;lupe<columns;++lupe)
            *ptr++ *= scaleValue;
    }

    /* **************************************************************
     * Routine to determine the Reduced Row Echelon Form of the matrix.
     * Performs the RREF in place with the current matrix.
     * ************************************************************** */
    void RREF()
    {
        // define various required variables.
        int outerLupe;
        int innerLupe;
        int currentPivotColumn = 0; // used to indicate the current pivot column

        // Go through each row in the matrix.
        // Figure out a new pivot row and then zero out the entries in the column
        // and and below the current row.
        for(outerLupe=0;(outerLupe<rows) && (currentPivotColumn<columns);++outerLupe)
        {

            // First figure out the current pivot.
            innerLupe = outerLupe; // assume that the pivot is in the first row available.
            while(currentPivotColumn < columns)
            {
                // Start with the current row and work down.
                if((fabs(u[innerLupe][currentPivotColumn])>1e-9))
                {
                    // This entry in this column and row non-zero. Stop here and use this.
                    break;
                }
                else
                {
                    // The entry in this column is essentially zero.
                    innerLupe += 1;    // check the next row.
                    if(innerLupe>=rows)
                    {
                        // We have hit the last row. Everything must be zero. Move over to the next column and start over.
                        innerLupe = outerLupe;
                        currentPivotColumn += 1;
                    }
                }
            }

            if (currentPivotColumn<columns)
            {
                // The current row and pivot are valid.
                // Can zero out the other rows in the current column

                // First see if we need to swap rows.
                if(innerLupe != outerLupe)
                {
                    // The next non-zero row is not the current row.
                    swapRows(innerLupe,outerLupe);
                }

                // zero out everything above the current pivot
                for(int lupe=0;lupe<outerLupe;++lupe)
                {
                    if(fabs(u[lupe][currentPivotColumn]) > 1e-9 )
                    {
                        // Need to zero out the column in this row....
                        daxpy(-u[lupe][currentPivotColumn]/u[outerLupe][currentPivotColumn],
                              lupe,outerLupe,currentPivotColumn);
                    }
                }

                // zero out everything below the current pivot
                for(int lupe=outerLupe+1;lupe<rows;++lupe)
                {
                    if(fabs(u[lupe][currentPivotColumn]) > 1e-9 )
                    {
                        // Need to zero out the column in this column....
                        daxpy(-u[lupe][currentPivotColumn]/u[outerLupe][currentPivotColumn],
                              lupe,outerLupe,currentPivotColumn);
                    }
                }

                // scale the row so that the entry in pivot column is equal to one.
                dscal(1.0/u[outerLupe][currentPivotColumn],outerLupe,currentPivotColumn);

            }

            // About to go on to the next row. Update the current pivot column to use the next column
            currentPivotColumn += 1;
        }


    }


    // Function to print out the whole array
    void printArray()
    {
        int innerLupe;
        int outerLupe;


        std::cout << std::endl << std::endl << getNumberRows() << "-" << getNumberColumns() << std::endl << "      ";

        // Print out the top row that has column numbers
        for(innerLupe=0;innerLupe<getNumberColumns();++innerLupe)
        {
            std::cout <<  "(" << std::setw(2) << innerLupe << ") ";
        }
        std::cout << std::endl;

        for (outerLupe=0;outerLupe<getNumberRows();++outerLupe)
        {
            std::cout << std::endl << "(" << outerLupe << ")" << getNumberRows()<< " ";
            for(innerLupe=0;innerLupe<getNumberColumns();++innerLupe)
            {
                std::cout <<  std::setw(4) << u[outerLupe][innerLupe]  << " ";
            }
        }
        std::cout << std::endl;
    }


protected:
    field **u = NULL;  // the matrix itslef.
    int rows = -1;     // number of rows in the matrix
    int columns = -1;  // number of columns in the matrix
    int* index;        // variable used to hold the current row permutations.
};


template <class field>
class squareMatrix : public matrix<field>
{
public:
    squareMatrix() : matrix<field>() {  }

    squareMatrix(int numberRows,field initialValue=0) : matrix<field>(numberRows,numberRows,initialValue) {}
    //squareMatrix(matrix<field>& A) : matrix<field>(A){createIndexPermutation();}

    /* *************************************************************************
     * Routine to copy over the columns of a given matrix into the rows
     * of this matrix. The columns to copy are given in a vector of integers.
     * ************************************************************************* */
    void copyColumnsToRows(matrix<field>& source,vector<int>indicies)
    {
        field* ptr;
        for(int rowLupe=0;rowLupe<this->rows;++rowLupe)
        {
            ptr = this->u[rowLupe];
            for(int lupe=0;lupe<this->columns;++lupe)
                *ptr++ = source[rowLupe][indicies[lupe]];
        }
    }

    // http://www.netlib.org/lapack/lug/node80.html
    // http://www.netlib.org/lapack/explore-html/d7/d3b/group__double_g_esolve_ga5ee879032a8365897c3ba91e3dc8d512.html#ga5ee879032a8365897c3ba91e3dc8d512
    // http://www.netlib.org/lapack/explore-html/dd/d9a/group__double_g_ecomputational_ga188b8d30443d14b1a3f7f8331d87ae60.html#ga188b8d30443d14b1a3f7f8331d87ae60


    /* *************************************************************************
     * Routine to perform an LU decomposition on the current matrix in place.
     * Calls the LAPACK dgetrf_ routine.
     * ************************************************************************* */
    int dgetrf()
    {
        // Set up the variables to pass to the LAPACK routine.
        int numRows = this->rows;
        int numCols = numRows;
        int LDA = numCols;
        int result;

        // Call LAPACK's dgetrf_ routine.
        dgetrf_(&numRows,&numCols,this->u[0],&LDA,this->index,&result);

        // print out the row permutations to see what happened...
        //std::cout << std::endl;
        //for(int lupe=0;lupe<this->rows;++lupe)
        //    std::cout << result << ":" << this->index[lupe] << std::endl;

        // Clean up and return the result.
        return(result);
    }

    /* *************************************************************************
     * Routine to approximate the norm of the current matrix.
     * Calls the LAPACK dlange_ routine.
     * ************************************************************************* */
    double dlange()
    {
        // Set up the parameters to send to the LAPACK method.
        char *whichNorm = "1";
        int numberRows = this->rows;
        int numberCols = numberRows;
        int LDA = numberRows;
        double *work = new double[4*numberRows];

        // Call the lapack routine to calc. the norm of the matrix.
        double norm = dlange_(whichNorm,&numberRows,&numberCols,this->u[0],&LDA,work);

        // Clean up and return the norm.
        delete [] work;
        return(norm);
    }

    /* *************************************************************************
     * Routine to approximate the reciprocal of the condition number of the
     * current matrix.
     * Calls the LAPACK dgecon_ routine.
     * ************************************************************************* */
    double dgecon(int performLU)
    {
        // see if the lu decomposition has been performed. If necessary
        // go ahead and decompose the matrix.
        if(performLU)
        {
            if(dgetrf()!=0)
                return(0.0);
        }

        // Determine the necessary parameters for the call to the routine
        // to estimate the condition number.
        char which = '1';
        int numRows = this->rows;
        int LDA = numRows;
        double norm = 1.0;
        double cond;
        double *work = new double[4*numRows];
        int *iwork   = new int[numRows];
        int result;

        // Call dgecon to get the condition number.
        dgecon_(&which,&numRows,this->u[0],&LDA,&norm,&cond,work,iwork,&result);

        // clean up the mess.
        delete [] work;
        delete [] iwork;

        // return the condition number.
        if(result==0)
            return(cond);
        else
            return(0.0);
    }


};

#endif // VECTOR_H
