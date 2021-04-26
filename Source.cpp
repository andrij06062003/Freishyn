#include <iostream>
#include<iomanip>
#include <string>
#define N 10
#define R 3

using namespace std;

class Competition         //клас олімпіадні завдання 
{
private:
    string name;
    string date;
public:
    string GetName()
    {
        return name;
    }
    void SetName(string name)
    {
        this->name = name;
    }

    string GetDate()
    {
        return date;
    }
    void SetDate(string date)
    {
        this->date = date;
    }
};

class TeamCompetition : public Competition         //похідний клас завдання
{
private:
    string team[R];
    int result[R];
    string team_l;
    int result_l;
public:
    string* GetTeam()
    {
        return team;
    }
    void SetTeam(string team, int i)
    {
        this->team[i] = team;
    }

    int* GetResult()
    {
        return result;
    }
    void SetResult(int result, int i)
    {
        this->result[i] = result;
    }

    string GetTeam_l()
    {
        return team_l;
    }
    void SetTeam_l(string team_l)
    {
        this->team_l = team_l;
    }

    int GetResult_l()
    {
        return result_l;
    }
    void SetResult_l(int result_l)
    {
        this->result_l = result_l;
    }

    friend int input(TeamCompetition* list);
    int Sum(TeamCompetition* list, int counter);
    friend void InsertionSort(TeamCompetition* list, int number);
    void Print(TeamCompetition* list, int counter);
};


int input(TeamCompetition* list)       //Введення даних
{
    static int kst = 0;
    while (1)
    {
        printf("\nВведіть інформацію про учасникiв змагань: \n"
            "Для завершення ведення впишіть '0'\n");
        cout << "\n№" << kst + 1 << "\nУніверситет:" << endl;
        string comp;
        getline(cin, comp);
        if (comp[0] == '0')    //Вихід з введеня , якщо перший символ '0'
        {
            return kst;
        }
        list[kst].SetName(comp);

        cout << "Дата проведення:" << endl;
        string date;
        getline(cin, date);
        list[kst].SetDate(date);
        int result;
        string team;
        for (int i = 0; i < R; i++) {
            cout << "Назва команди:";
            getline(cin, team);
            list[kst].SetTeam(team, i);
            cout << "Кількість перемог команди:";
            cin >> result;
            list[kst].SetResult(result, i);
            rewind(stdin);
        }
        cout << "Назва команди-лідера:" << '\n';
        string team_l;
        cin >> team_l;
        list[kst].SetTeam_l(team_l);
        cout << "Кількість перемог команди-лідера:";
        int result_l;
        cin >> result_l;
        list[kst].SetResult_l(result_l);
        rewind(stdin);
        kst++;
    }
}

int TeamCompetition::Sum(TeamCompetition* list, int counter)           //Підрахунок сумарної кількісті балів, набраних учасниками олімпіади
{
    int sum = 0;
    for (int i = 0; i < R; i++)
    {
        sum = result[i];
    }
    sum += list[counter].GetResult_l();
    return sum;
}


//сортування вставками
void InsertionSort(TeamCompetition* list, int number)
{
   int i, j, pos;
  int min;
  for (i = 0; i < number - 1; i++)  //вибираю елемент
  {
    pos = i;
    min = list[i].Sum(list, i);
    for (j = i + 1; j < number; j++)       //порівнюю його з усіма іншими
    {
      if (list[j].Sum(list, j) < min)      //найменший елемент зберігаю
      {
        pos = j;
        min = list[j].Sum(list, j);
      }
    }
    TeamCompetition temp;
    temp = list[pos];//та міняю місцями з вибраним
    list[pos] = list[i];
    list[i] = temp;
  }
}
void Print(TeamCompetition* list, int counter)
{
    int q;// видення даних у табличці
    cout << "\t\t\t\tВідсортована таблиця за зростанням набраних балів";
    cout << "\n.------------------------------------------------------------------------------------------------------------------."
        "\n| № |         Змагання         |   Дата проведення   | Команда лідер | Кількість перемог лідера | Сума всіх перемог  |"
        "\n:------------------------------------------------------------------------------------------------------------------:";
    for (q = 0; q < counter; q++)
    {
        cout << "\n| " << q + 1 << " | " << left << setw(33) << list[q].GetName() << "| ";
        cout << left << setw(23) << list[q].GetDate() << "|        " << left << setw(10) << list[q].GetTeam_l();
        cout << "|        " << left << setw(8) << list[q].GetResult_l() << "|      " << left << setw(8) << list[q].Sum(list, q) << "|";
    }
    cout << "\n'------------------------------------------------------------------------------------------------------------------'\n" << endl;
}



int main()
{
    system("chcp 1251");
    TeamCompetition list[N];
    int num;
    num = input(list);
    InsertionSort(list, num);
    Print(list, num);
}