#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>

class Matrix
{
	private:
		size_t height;
		size_t width;
		std::vector<std::vector<float> > values;

	public:
		Matrix();
		Matrix(size_t height, size_t width);
		Matrix(const Matrix& matrixToCopy);
		~Matrix();
		void display();
		void add(const Matrix& matrix);
		void add(float n);
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
		Matrix operator+(const Matrix& matrix) const;
		Matrix operator+(float n) const;
		Matrix operator-(float n) const;
		Matrix operator*(const Matrix& matrix) const;
		Matrix operator*(float n) const;
		Matrix operator/(float n) const;
		void resize(size_t newWidth, size_t newHeight);
};

#endif // MATRIX_H_INCLUDED
