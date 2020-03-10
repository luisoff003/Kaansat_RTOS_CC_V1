/**
 * @file CMatrixLib.c
 * @author klaxalk
 * @brief sources of CMatrixLib
 * 
 * @copyright GNU Public License
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
 */

#include "custom/CMatrixLib_V_01.h"

// add two vectors
void vector_float_add(vector_float * a, const vector_float * b) {
	
	// check dimension
	if (a->length == b->length) {
	
		int16_t i;
	
		for (i = 1; i <= a->length; i++) {
			
			vector_float_set(a, i, vector_float_get(a, i) + vector_float_get(b, i));
		}
	}
}

// subtract two vectors
void vector_float_subtract(vector_float * a, const vector_float * b) {

	// check dimension
	if (a->length == b->length) {

		int16_t i;

		for (i = 1; i <= a->length; i++) {

			vector_float_set(a, i, vector_float_get(a, i) - vector_float_get(b, i));
		}
	}
}

// add two vector a, b and write the answer to a
float vector_float_inner_product(const vector_float * a, const vector_float * b) {
	
	float output = 0;
	
	// check dimension
	if (a->length == b->length) {
		
		int16_t i;
		
		for (i = 1; i <= a->length; i++) {
			
			output += vector_float_get(a, i)*vector_float_get(b, i);
		}
	}
	
	return output;
}

void vector_float_outer_product(const vector_float * a, const vector_float * b, matrix_float * C) {
	
	// check dimension
	if ((a->length == C->height) && (b->length == C->width)) {
		
		int16_t i, j;
		
		for (i = 1; i <= a->length; i++) {
			
			for (j = 1; j <= b->length; j++) {
				
				matrix_float_set(C, i, j, vector_float_get(a, i)*vector_float_get(b, j));
			}
		}
	}
}

// multiplies a vector by a constant
void vector_float_times(vector_float * a, const float C) {
	
	int16_t i;
	
	for (i = 1; i <= a->length; i++) {
			
		vector_float_set(a, i, vector_float_get(a, i)*C);
	}
}

// copy vector b to a vector a
void vector_float_copy(vector_float * a, const vector_float * b) {
	
	// check dimension
	if (a->length == b->length) {
		
		memcpy(a->data, b->data, a->length*sizeof(float));
		a->orientation = b->orientation;
	}
}

// set particular cell of the matrix
void matrix_float_set(matrix_float * m, const int16_t h, const int16_t w, const float value) {
	
	m->data[(h-1)*m->width + w - 1] = value;
}
// set particular cell of the matrix
void matrix_double_set(matrix_double * m, const int16_t h, const int16_t w, const double value) {

    m->data[(h-1)*m->width + w - 1] = value;
}

// set the whole vector to the value
void vector_float_set_to(vector_float * v, const float value) {

	int16_t i;

	for (i = 1; i <= v->length; i++) {

		vector_float_set(v, i, value);
	}
}

// set the whole vector to zeros
void vector_float_set_zero(vector_float * v) {
	
	int16_t i;
	
	for (i = 1; i <= v->length; i++) {
		
		vector_float_set(v, i, 0);
	}
}

// get the particular cell of the matrix
float matrix_float_get(const matrix_float * m, const int16_t h, const int16_t w) {

    return m->data[(h-1)*m->width + w - 1];
}
float matrix_double_get(const matrix_double * m, const int16_t h, const int16_t w) {

    return m->data[(h-1)*m->width + w - 1];
}

// matrix transposition
void matrix_float_transpose(const matrix_float * a, matrix_float * C) {
	
	int16_t i, j;
	
	// dimensions must agree
	if ((a->width == C->height) && (a->height == C->width)) {
		

		for (i = 1; i <= a->height; i++) {
			
			for (j = 1; j <= a->width; j++) {

				matrix_float_set(C, j, i, matrix_float_get(a, i, j));
			}
		}
	}
}

// matrix transposition
void matrix_float_transpose_square(matrix_float * m) {
	
	int16_t i, j;
	float temp;
	
	for (i = 1; i <= m->height; i++) {
		
		for (j = i; j <= m->width; j++) {
			
			temp = matrix_float_get(m, i, j);
			matrix_float_set(m, i, j, matrix_float_get(m, j, i));
			matrix_float_set(m, j, i, temp);
		}
	}
}


// set all cells to value
void matrix_float_set_all(matrix_float * m, const float value) {
	
	int16_t i, j;
	
	for (i = 1; i <= m->height; i++) {
		
		for (j = 1; j <= m->width; j++) {
			
			matrix_float_set(m, i, j, value);
		}
	}
}
void matrix_double_set_all(matrix_double * m, const double value) {

    int16_t i, j;

    for (i = 1; i <= m->height; i++) {

        for (j = 1; j <= m->width; j++) {

            matrix_double_set(m, i, j, value);
        }
    }
}
// set matrix to zeros
void matrix_float_set_zero(matrix_float * m) {

    matrix_float_set_all(m, (float) 0);
}
void matrix_double_set_zero(matrix_double * m) {

    matrix_double_set_all(m, (float) 0);
}

// set matrix to identity matrix
void matrix_float_set_identity(matrix_float * m) {
	
	// matrix must be a square matrix
	if (m->width == m->height) {
	
		matrix_float_set_zero(m);
		
		int16_t i;
		
		for (i = 1; i <= m->height; i++) {
			
			matrix_float_set(m, i, i, (float) 1.0);
		}
	}
}
void matrix_double_set_identity(matrix_double * m) {

    // matrix must be a square matrix
    if (m->width == m->height) {

        matrix_double_set_zero(m);

        int16_t i;

        for (i = 1; i <= m->height; i++) {

            matrix_double_set(m, i, i, (double) 1.0);
        }
    }
}

// add two matrices
void matrix_float_copy(matrix_float * a, const matrix_float * b) {
    //memcpy(dest, src, strlen(src)+1);
	// matrices dimensions must agree
	if ((a->width == b->width) && (a->height == b->height)) {
		
		memcpy(a->data, b->data, a->height*a->width*sizeof(float));
	}
}
void matrix_double_copy(matrix_double * a, const matrix_double * b) {
    //memcpy(dest, src, strlen(src)+1);
    // matrices dimensions must agree
    if ((a->width == b->width) && (a->height == b->height)) {

        memcpy(a->data, b->data, a->height*a->width*sizeof(double));
    }
}

void matrix_double2float_copy(matrix_float * MOut, const matrix_double * MIn) {
    //memcpy(dest, src, strlen(src)+1);
    // matrices dimensions must agree
    int j_f=0, i_f=0;
    if ((MOut->width == MIn->width) && (MOut->height == MIn->height)) {
        for (j_f = 1; j_f <= MOut->height; ++j_f) {
            for (i_f = 1; i_f <= MOut->width; ++i_f) {
                matrix_float_set(MOut, j_f, i_f, (float)matrix_double_get(MIn, j_f, i_f));
            }
        }
    }
}
void matrix_float2double_copy(matrix_double * MOut, const matrix_float * MIn) {
    //memcpy(dest, src, strlen(src)+1);
    // matrices dimensions must agree
    int j_f=0, i_f=0;
    if ((MOut->width == MIn->width) && (MOut->height == MIn->height)) {
        for (j_f = 1; j_f <= MOut->height; ++j_f) {
            for (i_f = 1; i_f <= MOut->width; ++i_f) {
                matrix_double_set(MOut, j_f, i_f, (double)matrix_float_get(MIn, j_f, i_f));
            }
        }
    }
}


// add two matrices
void matrix_float_add(matrix_float * a, const matrix_float * b) {
	
	// matrices dimensions must agree
	if ((a->width == b->width) && (a->height == b->height)) {
		
		int16_t i, j;
	
		for (i = 1; i <= a->height; i++) {
		
			for (j = 1; j <= a->width; j++) {
			
				matrix_float_set(a, i, j, matrix_float_get(a, i, j) + matrix_float_get((matrix_float *) b, i, j));
			}
		}
	}
}


// subtract two matrices
void matrix_float_sub(matrix_float * a, const matrix_float * b) {
	
	// matrices dimensions must agree
	if ((a->width == b->width) && (a->height == b->height)) {
		
		int16_t i, j;
		
		for (i = 1; i <= a->height; i++) {
			
			for (j = 1; j <= a->width; j++) {
				
				matrix_float_set(a, i, j, matrix_float_get(a, i, j) - matrix_float_get((matrix_float *) b, i, j));
			}
		}
	}			
}

// set the particular cell of the vector
void vector_float_set(vector_float * v, const int16_t pos, const float value) {
	
	if (pos >= 1 && pos <= v->length) {
	
		v->data[pos-1] = value;	
	} else {
		
		// index out of bounds
	}
}

// set the particular cell of the vector
float vector_float_get(const vector_float * v, const int16_t pos) {
	
	if (pos >= 1 && pos <= v->length) {
	
		return v->data[pos-1];	
	}
	
	// else index out of bounds
	return 0;
}

// transpose the vector
void vector_float_transpose(vector_float * v) {

	if (v->orientation == 0)
		v->orientation = 1;
	else if (v->orientation == 1)
		v->orientation = 0;
}

// get row from matrix
void matrix_float_get_row(const matrix_float * m, vector_float * v, const int16_t row) {
	
	// the matrix width must be same as the vector length
	if ((v->length == m->width)) {
		
		int16_t i;
		
		for (i = 1; i <= m->width; i++) {
			
			vector_float_set(v, i, matrix_float_get(m, row, i));
		}
		
		// set orientation to horizontal
		v->orientation = 1;
	}
}

// get column from matrix
void matrix_float_get_col(const matrix_float * m, vector_float * v, const int16_t col) {
	
	// the matrix width must be same as the vector length
	if ((v->length == m->height)) {
		
		int16_t i;
		
		for (i = 1; i <= m->height; i++) {
			
			vector_float_set(v, i, matrix_float_get(m, i, col));
		}
		
		// set orientation to vertical
		v->orientation = 0;
	}
}

// multiply two matrices
void matrix_float_mul(const matrix_float * a, const matrix_float * b, matrix_float * C) {
	
	int16_t i, j, k;
	float tempSum;
	
	// dimensions must agree
	if (a->width == b->height && a->height == C->height && b->width == C->width) {
		
		for (i = 1; i <= C->height; i++) {
			
			for (j = 1; j <= C->width; j++) {
				
				tempSum = 0;
				for (k = 1; k <= a->width; k++) {
					tempSum += matrix_float_get(a, i, k)*matrix_float_get(b, k, j);
				}
				
				matrix_float_set(C, i, j, tempSum);
			}
		}
	}
}

// multiply two matrices, one of which is transposed, a*b'
void matrix_float_mul_trans(const matrix_float * a, const matrix_float * b, matrix_float * C) {
	
	int16_t i, j, k;
	float tempSum;
	
	// dimensions must agree
	if (a->width == b->width && a->height == C->height && b->height == C->width) {
		
		for (i = 1; i <= C->height; i++) {
			
			for (j = 1; j <= C->width; j++) {
				
				tempSum = 0;
				for (k = 1; k <= a->width; k++) {
					tempSum += matrix_float_get(a, i, k)*matrix_float_get(b, j, k);
				}
				
				matrix_float_set(C, i, j, tempSum);
			}
		}
	}
}

// multiply matrix by a constant
void matrix_float_times(matrix_float * a, const float C) {
	
	int16_t i, j;
	
	for (i = 1; i <= a->height; i++) {
		
		for (j = 1; j <= a->width; j++) {
			
			matrix_float_set(a, i, j, C*matrix_float_get(a, i, j));
		}
	}
}

// multiply a matrix by a vector from the right
void matrix_float_mul_vec_right(const matrix_float * m, const vector_float * v, vector_float * C) {
	
	int16_t i, j;
	float tempSum;
	
	// dimensions must agree
	if ((m->width == v->length) && (m->height == C->length)) {
		
		for (i = 1; i <= m->height; i++) {
			
			tempSum = 0;
			
			for (j = 1; j <= m->width; j++) {
			
				tempSum += matrix_float_get(m, i, j)*vector_float_get(v, j);	
			}
			vector_float_set(C, i, tempSum);
		}
	
		// set orientation to vertical
		C->orientation = 0;
	}	
}

// multiply a matrix by a vector from the left
void matrix_float_mul_vec_left(const matrix_float * m, const vector_float * v, vector_float * C) {
	
	int16_t i, j;
	float tempSum;
	
	// dimensions must agree
	if ((m->height == v->length) && (m->width == C->length)) {
		
		for (i = 1; i <= m->width; i++) {
			
			tempSum = 0;
			
			for (j = 1; j <= m->height; j++) {
				
				tempSum += matrix_float_get(m, j, i)*vector_float_get(v, j);
			}
			vector_float_set(C, i, tempSum);
		}

		// set orientation to horizontal
		C->orientation = 1;
	}
}

// compute the determinant of a matrix
float matrix_float_determinant(const matrix_float * a) {
    bauxf.data = (float *) &bauxfDat;
    bauxf.height = a->height;
    bauxf.width = a->width;

	// the matrix should be a square matrix
	if (a->width == a->height) {
		
		// special case, 1x1 matrix
		if (a->width == 1) {
			
			return(matrix_float_get(a, 1, 1));
		}
	
		int16_t i, j, k;
		float coeficient;
		float determinant = 1.0;

		// copy matrix a to a local temporary matrix
//		int16_t n = a->height;

//		float temp_matrix_data[n*n];
//		matrix_float temp_matrix;
//		temp_matrix.data = (float *) &temp_matrix_data;
//		temp_matrix.height = n;
//		temp_matrix.width = n;
//		temp_matrix.name = "Vypocet determinantu";
	
		// copy the specified matrix into temp_matrix
		matrix_float_copy(&bauxf, a);
	
		// start gauss elimination
		// for all rows
		for (i = 1; i <= a->height; i++) {
			
			// for all rows bellow it
			for (j = a->height; j > i; j--) {
				
				coeficient = matrix_float_get(&bauxf, j, i)/matrix_float_get(&bauxf, i, i);
				
				for (k = 1; k <= a->width; k++) {
				
					matrix_float_set(&bauxf, j, k, matrix_float_get(&bauxf, j, k) - coeficient*matrix_float_get(&bauxf, i, k));
				}
			}
		}
	
		for (i = 1; i <= a->width; i++) {
			
			determinant *= matrix_float_get(&bauxf, i, i);
		}
		
		return determinant;
	}
	
	return (float) 0;
}

double matrix_double_determinant(const matrix_double * a) {
    baux.data = (double *) &bauxDat;
    baux.height = a->height;
    baux.width = a->width;

    // the matrix should be a square matrix
    if (a->width == a->height) {

        // special case, 1x1 matrix
        if (a->width == 1) {

            return(matrix_double_get(a, 1, 1));
        }

        int16_t i, j, k;
        double coeficient;
        double determinant = 1.0;

        // copy matrix a to a local temporary matrix
//      int16_t n = a->height;

//      float temp_matrix_data[n*n];
//      matrix_float temp_matrix;
//      temp_matrix.data = (float *) &temp_matrix_data;
//      temp_matrix.height = n;
//      temp_matrix.width = n;
//      temp_matrix.name = "Vypocet determinantu";

        // copy the specified matrix into temp_matrix
        matrix_double_copy(&baux, a);

        // start gauss elimination
        // for all rows
        for (i = 1; i <= a->height; i++) {

            // for all rows bellow it
            for (j = a->height; j > i; j--) {

                coeficient = matrix_double_get(&baux, j, i)/matrix_double_get(&baux, i, i);

                for (k = 1; k <= a->width; k++) {

                    matrix_double_set(&baux, j, k, matrix_double_get(&baux, j, k) - coeficient*matrix_double_get(&baux, i, k));
                }
            }
        }

        for (i = 1; i <= a->width; i++) {

            determinant *= matrix_double_get(&baux, i, i);
        }

        return determinant;
    }

    return (double) 0;
}
// computer the inversion of matrix A, returns 0 if the inversion doesn't exist, 1 otherwise
int matrix_float_inverse(matrix_float * a) {
	
	// the matrix should be a square matrix
	if (a->width == a->height) {
	
		// special case, 1x1 matrix
		if (a->width == 1) {
			
			matrix_float_set(a, 1, 1, ((float) 1)/matrix_float_get(a, 1, 1));
			return 1;
		}	
		
//		float determinant = matrix_float_determinant(a);
		
		// check the matrix regularity
//		if (fabs(determinant) >= 0.0000001) {
			
			int16_t i, j, k;
			float coeficient;
	
			// copy matrix a to a local temporary matrix
			int16_t n = a->height;

//			float temp_matrix_data[n*n];
//			matrix_float temp_matrix;
//			temp_matrix.data = (float *) &temp_matrix_data;
//			temp_matrix.height = n;
//			temp_matrix.width = n;
//			temp_matrix.name = "Puvodni";
			
			// temp matrix2 for computing the covariance matrix
//			float temp_matrix2_data[n*n];
//			matrix_float temp_matrix2;
//			temp_matrix2.data = (float *) &temp_matrix2_data;
//			temp_matrix2.height = n;
//			temp_matrix2.width = n;
//			temp_matrix2.name = "Nova";


			// set one matrix as the specified matrix
			matrix_float_copy(&temp_matrixInv1, a);
			
			// set the other as diagonal
			matrix_float_set_identity(&temp_matrixInv2);
			
			// do complete gauss elimination
			
			// start elimination the bottom triangular matrix
			// for all rows
			for (i = 1; i <= n; i++) {
						
				// for all rows bellow it
				for (j = n; j > i; j--) {
							
					coeficient = matrix_float_get(&temp_matrixInv1, j, i)/matrix_float_get(&temp_matrixInv1, i, i);
							
					for (k = 1; k <= a->width; k++) {
								
						matrix_float_set(&temp_matrixInv1, j, k, matrix_float_get(&temp_matrixInv1, j, k) - coeficient*matrix_float_get(&temp_matrixInv1, i, k));
						matrix_float_set(&temp_matrixInv2, j, k, matrix_float_get(&temp_matrixInv2, j, k) - coeficient*matrix_float_get(&temp_matrixInv2, i, k));
					}
				}
			}
			
			// start elimination the top triangular matrix
			// for all rows
			for (i = n; i >= 1; i--) {
							
				// make 1 in bottom right corner
				coeficient = matrix_float_get(&temp_matrixInv1, i, i);
				for (k = 1; k <= a->width; k++) {
								
					matrix_float_set(&temp_matrixInv2, i, k, matrix_float_get(&temp_matrixInv2, i, k)/coeficient);
				}
				matrix_float_set(&temp_matrixInv1, i, i, (float) 1);
				
				// for all rows bellow it
				for (j = 1; j < i; j++) {
					
					coeficient = matrix_float_get(&temp_matrixInv1, j, i)/matrix_float_get(&temp_matrixInv1, i, i);
					
					for (k = 1; k <= a->width; k++) {
						
						matrix_float_set(&temp_matrixInv1, j, k, matrix_float_get(&temp_matrixInv1, j, k) - coeficient*matrix_float_get(&temp_matrixInv1, i, k));
						matrix_float_set(&temp_matrixInv2, j, k, matrix_float_get(&temp_matrixInv2, j, k) - coeficient*matrix_float_get(&temp_matrixInv2, i, k));
					}
				}
			}
			
			matrix_float_copy(a, &temp_matrixInv2);
			
		// matrix does not have its inversion
//		} else {
			
//			return 0;
//		}
	}
	
	return 1;
}



int matrix_InvMatDouble( matrix_double * Mi1 ,matrix_double * Mout)
{

    int i=0, j=0, k=0, Nt=Mi1->height*Mi1->width, N=Mi1->height;
    double sum=0.0,m=0.0;
    //  float *b=new float[Nt];//vector/matriz de (r1)*(c1) elementos


    //double b[49];//vector/matriz de (r1)*(c1) elementos
    baux.data = (double *) &bauxDat;
    baux.height = Mi1->height;
    baux.width = Mi1->width;

    //hacemos una matriz identidad
/*    //hacemos una matriz identidad
    for(j=0; j<N; j++)
    {
        for(i=0; i<N; i++)
        {
            if(i==j)
            {
                b[j*r1+i]=1.0;
            }
            else
            {
                b[j*r1+i]=0.0;
            }
        }
    }
*/
    matrix_double_set_identity(&baux);

/*    for(k=0; k<N-1; k++)
    {
        for(j=k+1; j<N; j++)
        {
            if(M1[k*r1+k]==0.0)
            {
                return(0);
            }
            m=M1[j*r1+k]/M1[k*r1+k];
            for(i=0; i<N; i++)
            {
                M1[j*r1+i]=M1[j*r1+i]-m*M1[k*r1+i];
                b[j*r1+i]=b[j*r1+i]-m*b[k*r1+i];
            }
        }
    }
*/

    //hacemos operaciones de renglon con la matriz
    for(k=0; k<N-1; k++)// k es el n�mero de rengl�n / columna
    {
        for(j=k+1; j<N; j++)// j es el n�mero de rengl�n
        {
            if(matrix_double_get(Mi1, k+1, k+1)==0.0)
            {
                return(0);
            }
            m=matrix_double_get(Mi1, j+1, k+1)/matrix_double_get(Mi1, k+1, k+1);
            for(i=0; i<N; i++)// i es el n�mero de columna
            {
                matrix_double_set(Mi1, j+1, i+1, matrix_double_get(Mi1, j+1, i+1)-m*matrix_double_get(Mi1, k+1, i+1));
                matrix_double_set(&baux, j+1, i+1, matrix_double_get(&baux, j+1, i+1)-m*matrix_double_get(&baux, k+1, i+1));
            }
        }
    }


/*    for(j=N-1; j>=0; j--)
    {
        for(i=0; i<N; i++)
        {
            sum=0.0;
            MOut[j*r1+i]=0.0;
            for(k=j+1; k<N; k++)
            {
                sum=sum+M1[j*r1+k]*MOut[k*r1+i];

            }
            if(M1[j*r1+j]==0.0)
            {
                return(0);
            }
            MOut[j*r1+i]=(b[j*r1+i]-sum)/M1[j*r1+j];
        }
    }
*/

    for(j=N-1; j>=0; j--)// j es el n�mero de rengl�n
    {
        for(i=0; i<N; i++)// i es el n�mero de columna
        {
            sum=0.0;
            matrix_double_set(Mout, j+1, i+1, 0.0);
            for(k=j+1; k<N; k++) // k es el n�mero de columna y rengl�n
            {

                sum=sum+matrix_double_get(Mi1, j+1, k+1)*matrix_double_get(Mout, k+1, i+1);

            }
            if(matrix_double_get(Mi1, j+1, j+1)==0.0)// j es el n�mero de rengl�n y columna
            {
                return(0);
            }
            matrix_double_set(Mout, j+1, i+1, ((matrix_double_get(&baux, j+1, i+1)-sum)/matrix_double_get(Mi1, j+1, j+1)));// j es el n�mero de rengl�n, i es de columna
        }
    }

    return(1);

}



