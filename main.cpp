/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlouise <davidlouiz@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 02:10:35 by dlouise           #+#    #+#             */
/*   Updated: 2015/11/26 20:42:07 by dlouise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Les tests definis ici seront effectues
#define TEST_CONSTRUCTORS
#define TEST_DISPLAY
#define TEST_ADD
#define TEST_EQUAL
#define TEST_DIFFERENT
#define TEST_SUBTRACT
#define TEST_GET_WIDTH
#define TEST_GET_HEIGHT
#define TEST_MULTIPLY
#define TEST_SET_VALUE
#define TEST_GET_VALUE
#define TEST_DIVIDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include "matrix.h"

int     test_constructors(void);
int     test_display(void);
int     test_add(void);
int     test_equal(void);
int     test_different(void);
int     test_subtract(void);
int     test_get_width(void);
int     test_get_height(void);
int     test_multiply(void);
int     test_set_value(void);
int     test_get_value(void);
int     test_divide(void);

#define ERROR() { printf("Line %d, ", __LINE__); return (0); }
#define ADD_TEST(NAME) add_test(tests_list, #NAME, test_##NAME)

typedef struct  s_test
{
    int         (*f)(void);
    const char  *name;
    char        added;
}               t_test;

void    add_test(t_test *tests_list, const char *name, int (*f)(void))
{
    static int  i = 0;

    tests_list[i].f = f;
    tests_list[i].name = name;
    tests_list[i].added = 1;
    i++;
}

int     main(void)
{
    t_test  tests_list[100];
    int     i;
    pid_t   pid;
    int     status;

    memset(tests_list, 0, 100 * sizeof(t_test));


#ifdef TEST_CONSTRUCTORS
    ADD_TEST(constructors);
#endif
#ifdef TEST_DISPLAY
    ADD_TEST(display);
#endif
#ifdef TEST_ADD
    ADD_TEST(add);
#endif
#ifdef TEST_EQUAL
    ADD_TEST(equal);
#endif
#ifdef TEST_DIFFERENT
    ADD_TEST(different);
#endif
#ifdef TEST_SUBTRACT
    ADD_TEST(subtract);
#endif
#ifdef TEST_GET_WIDTH
    ADD_TEST(get_width);
#endif
#ifdef TEST_GET_HEIGHT
    ADD_TEST(get_height);
#endif
#ifdef TEST_MULTIPLY
    ADD_TEST(multiply);
#endif
#ifdef TEST_SET_VALUE
    ADD_TEST(set_value);
#endif
#ifdef TEST_GET_VALUE
    ADD_TEST(get_value);
#endif
#ifdef TEST_DIVIDE
    ADD_TEST(divide);
#endif

    i = 0;
    while (tests_list[i].added)
    {
        printf("%s : ", tests_list[i].name);
        fflush(stdout);
        pid = fork();
        // Cas du fils
        if (0 == pid)
        {
            alarm(3);
            if (1 == tests_list[i].f())
                printf("\033[32mOK\033[0m\n");
            else
                printf("\033[31mKO\033[0m\n");
            exit(0);
        }
        // Cas du pere
        else
        {
            if (-1 != wait(&status) && WIFSIGNALED(status))
            {
                switch(WTERMSIG(status))
                {
                    case SIGSEGV:
                        printf("\033[31mSegmentation Fault\033[0m\n");
                        break;
                    default:
                        printf("\033[31mKO Sig %d\033[0m\n", WTERMSIG(status));
                }
            }
        }

        i++;
    }

    return (0);
}

#ifdef TEST_CONSTRUCTORS
int     test_constructors(void)
{
  Matrix a;
  if (a.getWidth() != 0)
    ERROR();
  if (a.getHeight() != 0)
    ERROR();
  Matrix b(3, 2);
  if (b.getWidth() != 2)
    ERROR();
  if (b.getHeight() != 3)
    ERROR();
  Matrix c(b);
  if (c.getWidth() != 2)
    ERROR();
  if (c.getHeight() != 3)
    ERROR();
  return (1);
}
#endif

#ifdef TEST_DISPLAY
int     test_display(void)
{
  int		out;
  int		p[2];
  char	output[100];

  out = dup(1);
  pipe(p);
  dup2(p[1], 1);

  Matrix a(3, 2);
  a.setValue(0, 1, 15.5);
  a.display();

  output[read(p[0], output, 100)] = '\0';
  if (0 != strcmp(output, "0\t15.5\t\n0\t0\t\n0\t0\t\n"))
  {
    dup2(out, 1);
    ERROR();
  }

  dup2(out, 1);
  return (1);
}
#endif

#ifdef TEST_ADD
int     test_add(void)
{
  Matrix a(3, 2);
  a.setValue(0, 0, 1);
  a.setValue(0, 1, 2);
  a.setValue(1, 0, 3);
  a.setValue(1, 1, 4);
  a.setValue(2, 0, 5);
  a.setValue(2, 1, 6);

  Matrix b(3, 2);
  b.setValue(0, 0, 10);
  b.setValue(0, 1, 20);
  b.setValue(1, 0, 30);
  b.setValue(1, 1, 40);
  b.setValue(2, 0, 50);
  b.setValue(2, 1, 60);

  Matrix c(3, 2);
  c.setValue(0, 0, 11);
  c.setValue(0, 1, 22);
  c.setValue(1, 0, 33);
  c.setValue(1, 1, 44);
  c.setValue(2, 0, 55);
  c.setValue(2, 1, 66);

  Matrix d(3, 2);
  d.setValue(0, 0, 13);
  d.setValue(0, 1, 24);
  d.setValue(1, 0, 35);
  d.setValue(1, 1, 46);
  d.setValue(2, 0, 57);
  d.setValue(2, 1, 68);

  if (a + b != c)
    ERROR();

  a += b;
  if (a != c)
    ERROR();

  if (a + 2 != d)
    ERROR();

  a += 2;

  if (a != d)
    ERROR();

  return (1);
}
#endif

#ifdef TEST_EQUAL
int     test_equal(void)
{
  Matrix a(3, 2);
  a.setValue(0, 0, 1);
  a.setValue(0, 1, 2);
  a.setValue(1, 0, 3);
  a.setValue(1, 1, 4);
  a.setValue(2, 0, 5);
  a.setValue(2, 1, 6);

  Matrix b(3, 2);
  b.setValue(0, 0, 1);
  b.setValue(0, 1, 2);
  b.setValue(1, 0, 3);
  b.setValue(1, 1, 4);
  b.setValue(2, 0, 5);
  b.setValue(2, 1, 666);

  if (a == b)
    ERROR();

  b.setValue(2, 1, 6);

  if ( ! (a == b))
    ERROR();

  b.setValue(0, 0, 0);

  if (a == b)
      ERROR();

  Matrix c(4, 2);
  c.setValue(0, 0, 1);
  c.setValue(0, 1, 2);
  c.setValue(1, 0, 3);
  c.setValue(1, 1, 4);
  c.setValue(2, 0, 5);
  c.setValue(2, 1, 6);

  if (a == c)
    ERROR();

  Matrix d(3, 3);
  d.setValue(0, 0, 1);
  d.setValue(0, 1, 2);
  d.setValue(1, 0, 3);
  d.setValue(1, 1, 4);
  d.setValue(2, 0, 5);
  d.setValue(2, 1, 6);

  if (a == d)
    ERROR();

  Matrix e;
  if (a == e)
    ERROR();

  return (1);
}
#endif

#ifdef TEST_DIFFERENT
int     test_different(void)
{
  Matrix a(3, 2);
  a.setValue(0, 0, 1);
  a.setValue(0, 1, 2);
  a.setValue(1, 0, 3);
  a.setValue(1, 1, 4);
  a.setValue(2, 0, 5);
  a.setValue(2, 1, 6);

  Matrix b(3, 2);
  b.setValue(0, 0, 1);
  b.setValue(0, 1, 2);
  b.setValue(1, 0, 3);
  b.setValue(1, 1, 4);
  b.setValue(2, 0, 5);
  b.setValue(2, 1, 666);

  if (! (a != b))
    ERROR();

  b.setValue(2, 1, 6);

  if (a != b)
    ERROR();

  b.setValue(0, 0, 0);

  if (! (a != b))
      ERROR();

  Matrix c(4, 2);
  c.setValue(0, 0, 1);
  c.setValue(0, 1, 2);
  c.setValue(1, 0, 3);
  c.setValue(1, 1, 4);
  c.setValue(2, 0, 5);
  c.setValue(2, 1, 6);

  if (! (a != c))
    ERROR();

  Matrix d(3, 3);
  d.setValue(0, 0, 1);
  d.setValue(0, 1, 2);
  d.setValue(1, 0, 3);
  d.setValue(1, 1, 4);
  d.setValue(2, 0, 5);
  d.setValue(2, 1, 6);

  if (! (a != d))
    ERROR();

  Matrix e;
  if (! (a != e))
    ERROR();

  return (1);
}
#endif

#ifdef TEST_SUBTRACT
int     test_subtract(void)
{
  Matrix a(3, 2);
  a.setValue(0, 0, 1);
  a.setValue(0, 1, 2);
  a.setValue(1, 0, 3);
  a.setValue(1, 1, 4);
  a.setValue(2, 0, 5);
  a.setValue(2, 1, 6);

  Matrix b(3, 2);
  b.setValue(0, 0, 10);
  b.setValue(0, 1, 20);
  b.setValue(1, 0, 30);
  b.setValue(1, 1, 40);
  b.setValue(2, 0, 50);
  b.setValue(2, 1, 60);

  Matrix c(3, 2);
  c.setValue(0, 0, 11);
  c.setValue(0, 1, 22);
  c.setValue(1, 0, 33);
  c.setValue(1, 1, 44);
  c.setValue(2, 0, 55);
  c.setValue(2, 1, 66);

  Matrix d(3, 2);
  d.setValue(0, 0, 13);
  d.setValue(0, 1, 24);
  d.setValue(1, 0, 35);
  d.setValue(1, 1, 46);
  d.setValue(2, 0, 57);
  d.setValue(2, 1, 68);

  if (d - 2 != c)
    ERROR();

  d -= 2;

  if (d != c)
    ERROR();

  if (c - b != a)
    ERROR();

  c -= b;
  if (c != a)
    ERROR();

  return (1);
}
#endif

#ifdef TEST_GET_WIDTH
int     test_get_width(void)
{
  Matrix a;
  if (a.getWidth() != 0)
    ERROR();

  Matrix b(2, 3);
  if (b.getWidth() != 3)
    ERROR();

  return (1);
}
#endif

#ifdef TEST_GET_HEIGHT
int     test_get_height(void)
{
  Matrix a;
  if (a.getHeight() != 0)
    ERROR();

  Matrix b(2, 3);
  if (b.getHeight() != 2)
    ERROR();

  return (1);
}
#endif

#ifdef TEST_MULTIPLY
int     test_multiply(void)
{
  Matrix a(3, 4);
  a.setValue(0, 0, -3);
  a.setValue(0, 1, 3);
  a.setValue(0, 2, 0);
  a.setValue(0, 3, -10);
  a.setValue(1, 0, 7);
  a.setValue(1, 1, -6);
  a.setValue(1, 2, 9);
  a.setValue(1, 3, 2);
  a.setValue(2, 0, -9);
  a.setValue(2, 1, 9);
  a.setValue(2, 2, 3);
  a.setValue(2, 3, -8);

  Matrix b(4, 2);
  b.setValue(0, 0, -8);
  b.setValue(0, 1, -5);
  b.setValue(1, 0, -4);
  b.setValue(1, 1, -7);
  b.setValue(2, 0, 11);
  b.setValue(2, 1, -8);
  b.setValue(3, 0, 11);
  b.setValue(3, 1, -9);

  Matrix c(3, 2);
  c.setValue(0, 0, -98);
  c.setValue(0, 1, 84);
  c.setValue(1, 0, 89);
  c.setValue(1, 1, -83);
  c.setValue(2, 0, -19);
  c.setValue(2, 1, 30);

  Matrix d(4, 2);
  d.setValue(0, 0, -16);
  d.setValue(0, 1, -10);
  d.setValue(1, 0, -8);
  d.setValue(1, 1, -14);
  d.setValue(2, 0, 22);
  d.setValue(2, 1, -16);
  d.setValue(3, 0, 22);
  d.setValue(3, 1, -18);

  if (a * b != c)
    ERROR();

  a *= b;
  if (a != c)
    ERROR();

  if (b * 2 != d)
    ERROR();

  b *= 2;

  if (b != d)
    ERROR();

  return (1);
}
#endif

#ifdef TEST_SET_VALUE
int     test_set_value(void)
{
  Matrix a(3, 4);
  a.setValue(0, 0, -3);
  a.setValue(0, 1, 3);
  a.setValue(0, 2, 0);
  a.setValue(0, 3, -10);
  a.setValue(1, 0, 7);
  a.setValue(1, 1, -6);
  a.setValue(1, 2, 9);
  a.setValue(1, 3, 2);
  a.setValue(2, 0, -9);
  a.setValue(2, 1, 9);
  a.setValue(2, 2, 3);
  a.setValue(2, 3, -8);

  try
  {
    a.setValue(3, 0, 0);
    ERROR();
  }
  catch(std::string e)
  {
  }

  try
  {
    a.setValue(0, 4, 0);
    ERROR();
  }
  catch(std::string e)
  {
  }

  return (1);
}
#endif

#ifdef TEST_GET_VALUE
int     test_get_value(void)
{
  Matrix a(3, 4);
  a.setValue(0, 0, -3);
  a.setValue(0, 1, 3);
  a.setValue(0, 2, 0);
  a.setValue(0, 3, -10);
  a.setValue(1, 0, 7);
  a.setValue(1, 1, -6);
  a.setValue(1, 2, 9);
  a.setValue(1, 3, 2);
  a.setValue(2, 0, -9);
  a.setValue(2, 1, 9);
  a.setValue(2, 2, 3);
  a.setValue(2, 3, -8);

  if (a.getValue(0, 0) != -3)
    ERROR();
  if (a.getValue(0, 1) != 3)
    ERROR();
  if (a.getValue(0, 2) != 0)
    ERROR();
  if (a.getValue(0, 3) != -10)
    ERROR();
  if (a.getValue(1, 0) != 7)
    ERROR();
  if (a.getValue(1, 1) != -6)
    ERROR();
  if (a.getValue(1, 2) != 9)
    ERROR();
  if (a.getValue(1, 3) != 2)
    ERROR();
  if (a.getValue(2, 0) != -9)
    ERROR();
  if (a.getValue(2, 1) != 9)
    ERROR();
  if (a.getValue(2, 2) != 3)
    ERROR();
  if (a.getValue(2, 3) != -8)
    ERROR();

  try
  {
    a.getValue(3, 0);
    ERROR();
  }
  catch(std::string e)
  {
  }

  try
  {
    a.getValue(0, 4);
    ERROR();
  }
  catch(std::string e)
  {
  }

  return (1);
}
#endif

#ifdef TEST_DIVIDE
int     test_divide(void)
{
  Matrix a(4, 2);
  a.setValue(0, 0, -8);
  a.setValue(0, 1, -5);
  a.setValue(1, 0, -4);
  a.setValue(1, 1, -7);
  a.setValue(2, 0, 11);
  a.setValue(2, 1, -8);
  a.setValue(3, 0, 11);
  a.setValue(3, 1, -9);

  Matrix b(4, 2);
  b.setValue(0, 0, -16);
  b.setValue(0, 1, -10);
  b.setValue(1, 0, -8);
  b.setValue(1, 1, -14);
  b.setValue(2, 0, 22);
  b.setValue(2, 1, -16);
  b.setValue(3, 0, 22);
  b.setValue(3, 1, -18);

  if (b / 2 != a)
    ERROR();

  b /= 2;

  if (a != b)
    ERROR();

  return (1);
}
#endif
