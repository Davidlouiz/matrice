#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>

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

	public:
		Matrix(); // checked
		Matrix(size_t height, size_t width); // checked
		Matrix(const Matrix& matrixToCopy); // checked
		void display(); // checked
		void subtract(const Matrix& matrix);
		void subtract(float n);
		void multiply(const Matrix& matrix);
		void multiply(float n);
		void divide(const Matrix& matrix);
		void divide(float n);
		size_t getWidth(void) const;
		size_t getHeight(void) const;
		void setValue(size_t line, size_t column, float value);
		float getValue(size_t line, size_t column) const;
		std::vector<std::vector<float> > getValues(void) const;
		std::vector<float> operator[] (size_t x) const;
		Matrix operator+(const Matrix& matrix) const; // checked
		Matrix operator+(float n) const; // checked
		Matrix operator-(const Matrix& matrix) const;
		Matrix operator-(float n) const;
		Matrix operator*(const Matrix& matrix) const;
		Matrix operator*(float n) const;
		Matrix operator/(float n) const;
    bool operator==(const Matrix& matrix) const; // checked
    bool operator!=(const Matrix& matrix) const; // checked
    Matrix& operator+=(const Matrix& matrix); // checked
    Matrix& operator+=(float n); // checked
    Matrix& operator-=(const Matrix& matrix); // checked
    Matrix& operator-=(float n); // checked
};

#endif // MATRIX_H_INCLUDED
