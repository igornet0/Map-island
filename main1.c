#include <stdio.h>

#define N 10
#define len 100
#define X 5

int line_check(char vert_string[N], int arr_horiz[N]) {
  int arr[X] = {0}, ind_field_string = 0, ind_nums_arr = 0, kol_sim = 0, i = 0;
  
  while (vert_string[ind_field_string] != '$') {

    if (vert_string[ind_field_string] == '#') {
      kol_sim = 0;
      while (vert_string[ind_field_string] != '_' && vert_string[ind_field_string] != '$') {
        kol_sim++;
        ind_field_string++;
      }
      arr[ind_nums_arr] = kol_sim;
      ind_nums_arr++;
      if (vert_string[ind_field_string] == '$')
        break;
    }
    ind_field_string++;
  }

  while (arr_horiz[i] != 0) {
    if (arr_horiz[i] != arr[i])
      return 0;
    i++;
  }
  if (arr_horiz[i] == 0 && arr[i] != 0)
    return 0;
  return 1;
}

int field_check(char field[N][N], int arr_horiz[N][X], int size, char arr_perever[N]) {
  int i = 0;
  while (i < N - 1) {
    arr_perever[i] = '_';
    i++;
  }
  arr_perever[i - 1] = '$';
  int x = 0, y = 0;
  while (y < size) {
    x = 0;
    while (x < size) {
      arr_perever[x] = field[x][y];
      x++;
    }
    if (!(line_check(arr_perever, arr_horiz[y]))) {
      return 0;
    }
    y++;
  }
  return 1;
}

void correct_solution(char field[N][N], int size, FILE *f2) {
  int x = 0, y = 0;

  while (x < size) {
    y = 0;
    while (y < size) {
      if (field[x][y] == '#') {
        printf("* ");
        fprintf(f2, "* ");
      }
      else if (field[x][y] == '_') {
        printf("  ");
        fprintf(f2, "  ");
      }
      y++;
    }
    x++;
    printf("\n");
    fprintf(f2, "\n");
  }
}


int move_ready(char field[N]) {
  int num = 0, ind = 0, num_island = 0;
  while (field[ind] != '$') {
    if (field[ind] == '#') {
      while (field[ind] != '_' && field[ind] != '$') {
        ind++;
      }
      num++;
      if (field[ind] == '$')
        break;
      if (field[ind + 1] == '_' || field[ind + 1] == '$')
        num_island = num;
    }
    ind++;
  }
  return num_island;
}


int move_check(char field[N], int num) {

  int i = 0, j = 0; 
  while (i < num) {
    if (field[j] == '#') {
      while (field[j] != '_' && field[j] != '$') {
        j++;
      }
      i++;
      if (field[j] == '$')
        return 0;
    }
    j++;
  }
  j--;

  if (field[j] == '$')
    return 0;
  if (field[j + 1] == '#')
    return 0;
  return 1;
}


int search_end(char field_vert_string[N]) {
  int ind = 0, fl = 1; 

  while (field_vert_string[ind] != '$') {
    if (field_vert_string[ind] == '_')
      ind++;
    else
      break;
  }
  if (field_vert_string[ind] == '$')
    return 1;

  ind = 0;
  while (field_vert_string[ind] != '$') {

    if (field_vert_string[ind] == '#' && field_vert_string[ind + 1] == '_' && (field_vert_string[ind + 2] == '_' || field_vert_string[ind + 2] == '$'))
      return 0;


    if (field_vert_string[ind] == '#' && field_vert_string[ind + 1] == '$' && fl == 1)
      return 1;
    ind++;
  }
}


void left_move(char field[N], int num, int string[X], int kol_sim_in_string) {

  int i = 0, j = 0, z = 0; 
  while (i < num) {
    if (field[j] == '#') {
      while (field[j] != '_') {
        j++;
      }
      i++;
    }
    j++;
  }
  i = j;

  while (field[j] != '$') {
    field[j] = '_';
    j++;
  }

  while (num < kol_sim_in_string) {
    z = 0;
    while (z < string[num]) {
      field[i + z] = '#';
      z++;
    }
    num++;
    i = i + z + 1;
  }
}


void cell_move(char field[N], int num) {

  int i = 0, j = 0, i_down = 0;
  while (i < num) {
    if (field[j] == '#') {
      i_down = j;
      while (field[j] != '_') {
        j++;
      }
      i++;
    }
    j++;
  }
  j--;
  field[i_down] = '_';
  field[j] = '#';
}


int line_checking(char vert_string[N], int arr_horiz[N]) {
  int arr[X] = { 0 }, ind_field_string = 0, ind_nums_arr = 0, kol_sim = 0;
  
  while (vert_string[ind_field_string] != '$') {
    if (vert_string[ind_field_string] == '#') {
      kol_sim = 0;
      while (vert_string[ind_field_string] != '_' && vert_string[ind_field_string] != '$') {
        kol_sim++;
        ind_field_string++;
      }
      arr[ind_nums_arr] = kol_sim;
      ind_nums_arr++;
      if (vert_string[ind_field_string] == '$')
        break;
    }
    ind_field_string++;
  }

  int i = 0;

  while (arr_horiz[i] != 0) {
    if (arr_horiz[i] < arr[i])
      return 0;
    if ((arr_horiz[i] > arr[i]) && (arr[i + 1] != 0))
      return 0;
    i++;
  }
  if (arr_horiz[i] == 0 && arr[i] != 0)
    return 0;
  return 1;
}




int field_checking(char field[N][N], int arr_horiz[N][X], int size, char arr_perever[N]) {
  int i = 0, x = 0, y = 0;
  
  while (i < N - 1) {
    arr_perever[i] = '_';
    i++;
  }
  arr_perever[i-1] = '$';

  while (y < size) {
    x = 0;
    while (x < size) {
      arr_perever[x] = field[x][y];
      x++;
    }
    if (!(line_checking(arr_perever, arr_horiz[y]))) {
      return 0;
    }
    y++;
  }
  return 1;
}

void overchargeback(char field[N][N], int arr_vert[N][X], int arr_horiz[N][X], int num_of_string, int size, char unchecked_str[N], char arr_perever[N], int * megaflag, FILE * f2) {
  int a, i, j, z, kol_chisel_in_arr_vert;
  int x = 0, flag = 0, q, w, num_seeked_island, fl_for_string = 0;
  q = 0;
  x = 0;
  while (x < size) {
    unchecked_str[x] = '_';
    x++;
  }
  unchecked_str[size] = '$';

  do {
    a = 0; 
    kol_chisel_in_arr_vert = 0;
    do {
      kol_chisel_in_arr_vert++;
      a = arr_vert[num_of_string][kol_chisel_in_arr_vert];
    } while (a != 0);

    if (fl_for_string == 0 && arr_vert[num_of_string][0] != 0) {
      i = 0; 
      j = 0; 
      z = 0; 
      while (j < kol_chisel_in_arr_vert) {
        z = 0;
        while (z < arr_vert[num_of_string][j]) {
          unchecked_str[z + i] = '#';
          z++;
        }
        j++;
        i = i + z + 1;
      }
      fl_for_string = 1;
    }
    else if (arr_vert[num_of_string][0] != 0) {
      num_seeked_island = (move_ready(unchecked_str));
      cell_move(unchecked_str, num_seeked_island);
      left_move(unchecked_str, num_seeked_island, arr_vert[num_of_string], kol_chisel_in_arr_vert);
    }

    // запись в field
    q = 0;
    w = 0;
    while (q < size) {
      field[num_of_string][q] = unchecked_str[q];
      q++;
    }

    if (field_checking(field, arr_horiz, size, arr_perever)) {
      if (num_of_string < size - 1) {
        overchargeback(field, arr_vert, arr_horiz, num_of_string + 1, size, unchecked_str, arr_perever, megaflag, f2);

        x = 0;
        while (x < size) {
          unchecked_str[x] = field[num_of_string][x];
          x++;
        }

      }
      else if (field_check(field, arr_horiz, size, arr_perever)) {
        correct_solution(field, size, f2);
        printf("\n");
        fprintf(f2, "\n");
        x = 0;
        while (x < size) {
          field[num_of_string][x] = '_';
          x++;
        }
        field[num_of_string][x] = '$';

        *megaflag = 1;
      }
    }

    if (search_end(unchecked_str)) { 
      //стираем 
      x = 0;
      while (x < size) {
        field[num_of_string][x] = '_';
        x++;
      }
      field[num_of_string][x] = '$';
    }

  } while (!(search_end(unchecked_str)));
}



int main() {
  
  char field_of_islands[N][N];

  int n, i = 0, j = 0, a, x, q, w, s = 0;
  int horizontal[N][X], vertical[N][X];
  
  char not_checked_yet_string[N] = { "________$" };
  char arr_perever[N] = { "________$"};
  char str[len];
  
  FILE * f1;
  FILE * f2;
  
  int * solution_exist;
  
  f1 = fopen("C://Users//bagir//OneDrive//Рабочий стол//input4.txt", "r");
  f2 = fopen("C://Users//bagir//OneDrive//Рабочий стол//output4.txt", "w");


  while (!(feof(f1))) {
    fscanf(f1, "%d", &n);
    printf("%d\n", n);
    i = 0;
    while (i != n) {
      j = 0;
      do {
        fscanf(f1, "%d", &a);
        vertical[i][j] = a;
        j++;
        printf("%d ", a);
      } while (a != 0);
      printf("\n");
      i++;
    }

    i = 0;
    while (i != n) {
      j = 0;
      do {
        fscanf(f1, "%d", &a);
        horizontal[i][j] = a;
        j++;
        printf("%d ", a);
      } while (a != 0);
      printf("\n");
      i++;
    }

    x = 0;
    while (x < n) {
      not_checked_yet_string[x] = '_';
      x++;
    }
    not_checked_yet_string[n] = '$';

    q = 0;
    w = 0;
    while (q < n) {
      w = 0;
      while (w < n) {
        field_of_islands[q][w] = '_';
        w++;
      }
      field_of_islands[q][w] = '$';
      q++;
    }
    w = 0;
    while (w < n) {
      field_of_islands[n][w] = '$';
      w++;
    }

    s = 0;
    solution_exist = &s;
    printf("next problem\n");
    fprintf(f2, "next problem\n");
    overchargeback(field_of_islands, vertical, horizontal, 0, n, not_checked_yet_string, arr_perever, solution_exist, f2);
    if (*solution_exist == 0) {
      printf("no map\n");
      fprintf(f2, "no map\n");
    }
  }

  fclose(f1);
  fclose(f2);
  
  return 0;
}
