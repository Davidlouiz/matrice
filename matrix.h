#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>

#if defined (linux)
# include <sys/types.h>
#endif

class Matrix
{
	private:
		size_t height;
		size_t width;
		std::vector<std::vector<float> > values;
    bool equal(const Matrix& matrix) const;
		void resize(size_t newWidth, size_t newHeight);
		void add(const Matrix& matrix);
		void add(float n);
		void subtract(const Matrix& matrix);
		void subtract(float n);
		void multiply(const Matrix& matrix);
		void multiply(float n);
		std::vector<std::vector<float> > getValues(void) const;
		std::vector<float> operator[] (size_t x) const;
		void divide(float n);

	public:
		Matrix();
		Matrix(size_t height, size_t width);
		Matrix(const Matrix& matrixToCopy);
		void display() const;
		size_t getWidth(void) const;
		size_t getHeight(void) const;
		void setValue(size_t line, size_t column, float value);
		float getValue(size_t line, size_t column) const;
		Matrix operator+(const Matrix& matrix) const;
		Matrix operator+(float n) const;
		Matrix operator-(const Matrix& matrix) const;
		Matrix operator-(float n) const;
		Matrix operator*(const Matrix& matrix) const;
		Matrix operator*(float n) const;
		Matrix operator/(float n) const;
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator+=(float n);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator-=(float n);
    Matrix& operator*=(const Matrix& matrix);
    Matrix& operator*=(float n);
    Matrix& operator/=(float n);
};

#endif // MATRIX_H_INCLUDED
