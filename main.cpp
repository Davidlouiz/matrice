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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "matrix.h"

int     test_constructors(void);
int     test_display(void);
int     test_add(void);
int     test_equal(void);
int     test_different(void);
int     test_subtract(void);

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
