#include "matrix.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

Matrix::Matrix()
{
  this->width = 0;
  this->height = 0;
}

Matrix::Matrix(size_t height, size_t width)
{
  this->width = width;
  this->height = height;
  for (size_t i = 0; i < height; i++)
  {
     std::vector<float> line;
    for (size_t j = 0; j < width; j++)
    {
      line.push_back(0.0);
    }
    this->values.push_back(line);
  }
}

Matrix::Matrix(const Matrix& matrixToCopy)
{
  this->width = matrixToCopy.getWidth();
  this->height = matrixToCopy.getHeight();
  this->values = matrixToCopy.getValues();
}

void Matrix::display() const
{
	for(size_t line = 0; line < this->height; line++)
	{
		for(size_t column = 0; column < this->width; column++)
		{
			std::cout << this->values[line][column] << "\t";
		}
		std::cout << std::endl;
	}
}

void Matrix::add(const Matrix& matrix)
{
  size_t newWidth = std::min(this->width, matrix.getWidth());
  size_t newHeight = std::min(this->height, matrix.getHeight());

  this->values.resize(newHeight);

  for (size_t i = 0; i < this->values.size(); i++)
  {
    this->values[i].resize(newWidth);
  }

  for (size_t line = 0; line < newHeight; line++)
  {
    for (size_t column = 0; column < newWidth; column++)
    {
      this->values[line][column] += matrix.getValue(line, column);
    }
  }

  this->width = newWidth;
  this->height = newHeight;
}

void Matrix::add(float n)
{
  for (size_t line = 0; line < this->height; line++)
  {
    for (size_t column = 0; column < this->width; column++)
    {
      this->values[line][column] += n;
    }
  }
}

void Matrix::subtract(const Matrix& matrix)
{
  size_t newWidth = std::min(this->width, matrix.getWidth());
  size_t newHeight = std::min(this->height, matrix.getHeight());

  this->values.resize(newHeight);

  for (size_t i = 0; i < this->values.size(); i++)
  {
    this->values[i].resize(newWidth);
  }

  for (size_t line = 0; line < newHeight; line++)
  {
    for (size_t column = 0; column < newWidth; column++)
    {
      this->values[line][column] -= matrix.getValue(line, column);
    }
  }

  this->width = newWidth;
  this->height = newHeight;
}

void Matrix::subtract(float n)
{
  this->add(-n);
}

void Matrix::multiply(const Matrix& matrix)
{
  Matrix a = *this;
  Matrix b = matrix;

  if (a.getWidth() != b.getHeight())
  {
    throw std::string("The number of lines of matrix A must correspond to the number of columns of matrix B");
  }

  size_t newWidth = b.getWidth();
  size_t newHeight = a.getHeight();

  Matrix c;
  c.resize(newWidth, newHeight);

  for (size_t column = 0; column < newWidth; column++)
  {
    for (size_t line = 0; line < newHeight; line++)
    {
      float somme = 0.0;

      for (size_t i = 0; i < a.getWidth(); i++)
      {
        somme += a[line][i] * b[i][column];
      }
      c.setValue(line, column, somme);
    }
  }

  *this = c;
}

void Matrix::multiply(float n)
{
  for (size_t line = 0; line < this->height; line++)
  {
    for (size_t column = 0; column < this->width; column++)
    {
      this->setValue(line, column, this->values[line][column] * n);
    }
  }
}

void Matrix::divide(float n)
{
  this->multiply(1/n);
}


void Matrix::setValue(size_t line, size_t column, float valeur)
{
  if (column >= this->width || line >= this->height)
  {
    std::stringstream flux;
    flux << "The case [" << line << "," << column << "] doesn't exist : " << std::endl << "Height : " << this->height << std::endl << "Width : " << this->width << std::endl;
    throw flux.str();
  }
  this->values[line][column] = valeur;
}

size_t Matrix::getWidth(void) const
{
  return this->width;
}

size_t Matrix::getHeight(void) const
{
  return this->height;
}

float Matrix::getValue(size_t line, size_t column) const
{
  if (column >= this->width || line >= this->height)
  {
    std::stringstream flux;
    flux << "The case [" << line << "," << column << "] doesn't exist : " << std::endl << "Height : " << this->height << std::endl << "Width : " << this->width << std::endl;
    throw flux.str();
  }
  return this->values[line][column];
}

std::vector<std::vector<float> > Matrix::getValues(void) const
{
  return this->values;
}

std::vector<float> Matrix::operator[] (size_t line) const
{
  return this->values[line];
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
  Matrix result(*this);
  result.add(matrix);
  return result;
}

Matrix Matrix::operator+(float n) const
{
  Matrix result(*this);
  result.add(n);
  return result;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
  Matrix result(*this);
  result.subtract(matrix);
  return result;
}

Matrix Matrix::operator-(float n) const
{
  Matrix result(*this);
  result.subtract(n);
  return result;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
  Matrix result(*this);
  result.multiply(matrix);
  return result;
}

Matrix Matrix::operator*(float n) const
{
  Matrix result(*this);
  result.multiply(n);
  return result;
}

Matrix Matrix::operator/(float n) const
{
  Matrix result(*this);
  result.divide(n);
  return result;
}

void Matrix::resize(size_t newWidth, size_t newHeight)
{
  this->values.resize(newHeight);
  for (size_t i = 0; i < this->values.size(); i++)
  {
    this->values[i].resize(newWidth);
  }
  this->width = newWidth;
  this->height = newHeight;
}

bool Matrix::equal(const Matrix& matrix) const
{
  if (this->getWidth() != matrix.getWidth())
    return false;
  if (this->getHeight() != matrix.getHeight())
    return false;

  for (size_t column = 0; column < this->getWidth(); column++)
  {
    for (size_t line = 0; line < this->getHeight(); line++)
    {
      if (this->getValue(line, column) != matrix.getValue(line, column))
        return false;
    }
  }
  return true;
}

bool Matrix::operator==(const Matrix& matrix) const
{
  return this->equal(matrix);
}

bool Matrix::operator!=(const Matrix& matrix) const
{
  return ! this->equal(matrix);
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
    this->add(matrix);
    return *this;
}

Matrix& Matrix::operator+=(float n)
{
  this->add(n);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
    this->subtract(matrix);
    return *this;
}

Matrix& Matrix::operator-=(float n)
{
  this->subtract(n);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix)
{
    this->multiply(matrix);
    return *this;
}

Matrix& Matrix::operator*=(float n)
{
  this->multiply(n);
  return *this;
}

Matrix& Matrix::operator/=(float n)
{
  this->divide(n);
  return *this;
}
